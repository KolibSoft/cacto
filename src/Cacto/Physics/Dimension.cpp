#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Graphics/Rectangle.hpp>
#include <Cacto/Physics/Collisionable.hpp>
#include <Cacto/Physics/Dimension.hpp>

namespace cacto
{

    bool Dimension::hasZone(const sf::FloatRect &zone) const
    {
        auto result = zoneIn(m_zone, zone);
        return result;
    }

    Dimension *const Dimension::locate(const sf::FloatRect &zone) const
    {
        if (m_subdimensions)
        {
            if (m_topLeft->hasZone(zone))
                return m_topLeft;
            if (m_topRight->hasZone(zone))
                return m_topRight;
            if (m_bottomRight->hasZone(zone))
                return m_bottomRight;
            if (m_bottomRight->hasZone(zone))
                return m_bottomRight;
        }
        return nullptr;
    }

    void Dimension::append(Collisionable &body, const Trace &trace)
    {
        Holder holder;
        holder.body = &body;
        holder.trace = &trace;
        holder.invalid = true;
        holder.boundsArray = {};
        holder.geometryArray = {};
        append(holder);
    }

    void Dimension::collisions(Collisionable &body, const Trace &trace)
    {
        Holder holder;
        holder.body = &body;
        holder.trace = &trace;
        holder.invalid = true;
        holder.boundsArray = {};
        holder.geometryArray = {};
        collisions(holder);
    }

    void Dimension::collisionsChildren(Collisionable &body, const Trace &trace)
    {
        Holder holder;
        holder.body = &body;
        holder.trace = &trace;
        holder.invalid = true;
        holder.boundsArray = {};
        holder.geometryArray = {};
        collisionsChildren(holder);
    }

    Dimension &Dimension::locateCollisions(Collisionable &body, const Trace &trace)
    {
        Holder holder;
        holder.body = &body;
        holder.trace = &trace;
        holder.invalid = true;
        holder.boundsArray = {};
        holder.geometryArray = {};
        auto &target = Dimension::locateCollisions(*this, holder);
        return target;
    }

    bool Dimension::isEmpty() const
    {
        auto empty = m_holders.size() == 0 && !m_subdimensions ||
                     m_topLeft->isEmpty() && m_topRight->isEmpty() &&
                         m_bottomLeft->isEmpty() && m_bottomRight->isEmpty();
        return empty;
    }

    void Dimension::clean()
    {
        m_holders.clear();
        if (m_subdimensions)
        {
            m_topLeft->clean();
            m_topRight->clean();
            m_bottomLeft->clean();
            m_bottomRight->clean();

            if (m_subdimensions &&
                m_topLeft->isEmpty() && m_topRight->isEmpty() &&
                m_bottomLeft->isEmpty() && m_bottomRight->isEmpty())
            {
                delete m_topLeft;
                delete m_topRight;
                delete m_bottomLeft;
                delete m_bottomRight;
                m_subdimensions = false;
            }
        }
    }

    Dimension::Dimension(const sf::FloatRect &zone, szt capacity)
        : m_zone(zone), m_capacity(capacity), m_holders(), m_subdimensions(false),
          m_topLeft(nullptr), m_topRight(nullptr),
          m_bottomLeft(nullptr), m_bottomRight(nullptr),
          m_invalid(true),
          m_array()
    {
        if (capacity < 1)
            capacity = 1;
    }

    Dimension::~Dimension()
    {
        if (m_subdimensions)
        {
            delete m_topLeft;
            delete m_topRight;
            delete m_bottomLeft;
            delete m_bottomRight;
            m_subdimensions = false;
        }
    }

    Dimension::Dimension(const Dimension &other)
        : m_zone(other.m_zone), m_capacity(other.m_capacity), m_holders(), m_subdimensions(false),
          m_topLeft(nullptr), m_topRight(nullptr),
          m_bottomLeft(nullptr), m_bottomRight(nullptr),
          m_invalid(true),
          m_array()
    {
    }

    Dimension &Dimension::operator=(const Dimension &other)
    {
        m_zone = other.m_zone;
        m_capacity = other.m_capacity;
        if (m_subdimensions)
        {
            delete m_topLeft;
            delete m_topRight;
            delete m_bottomLeft;
            delete m_bottomRight;
            m_subdimensions = false;
        }
        m_invalid = true;
        return *this;
    }

    void Dimension::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (m_invalid)
        {
            m_array.setPrimitiveType(sf::PrimitiveType::LineStrip);
            setPoints(m_array, Rectangle({m_zone.left, m_zone.top}, {m_zone.width, m_zone.height}));
            m_array.append(m_array[0]);
            setColor(m_array, sf::Color::Magenta);
            target.draw(m_array, states);
            m_invalid = false;
        }
        if (m_subdimensions)
        {
            m_topLeft->draw(target, states);
            m_topRight->draw(target, states);
            m_bottomLeft->draw(target, states);
            m_bottomRight->draw(target, states);
        }
        for (auto &holder : m_holders)
        {
            if (holder.invalid)
            {
                auto bounds = holder.trace->getBounds();
                holder.boundsArray.setPrimitiveType(sf::PrimitiveType::LineStrip);
                setPoints(holder.boundsArray, Rectangle({bounds.left, bounds.top}, {bounds.width, bounds.height}));
                holder.boundsArray.append(holder.boundsArray[0]);
                setColor(holder.boundsArray, sf::Color::Blue);

                holder.geometryArray.setPrimitiveType(sf::PrimitiveType::LineStrip);
                setPoints(holder.geometryArray, holder.trace->getGeometry());
                holder.geometryArray.append(holder.geometryArray[0]);
                setColor(holder.geometryArray, sf::Color::Red);

                holder.invalid = false;
            }

            target.draw(holder.boundsArray, states);
            auto _states = states;
            _states.transform *= holder.trace->getTransform();
            target.draw(holder.geometryArray, _states);
        }
    }

    void Dimension::append(const Holder &holder)
    {
        m_holders.push_back(holder);
        if (m_holders.size() > m_capacity)
            split();
    }

    void Dimension::split()
    {
        if (!m_subdimensions)
        {
            auto width = m_zone.width / 2;
            auto height = m_zone.height / 2;
            m_topLeft = new Dimension(sf::FloatRect{{m_zone.left, m_zone.top},
                                                    {width, height}},
                                      m_capacity);
            m_topRight = new Dimension(sf::FloatRect{{m_zone.left + width, m_zone.top},
                                                     {width, height}},
                                       m_capacity);
            m_bottomLeft = new Dimension(sf::FloatRect{{m_zone.left, m_zone.top + height},
                                                       {width, height}},
                                         m_capacity);
            m_bottomRight = new Dimension(sf::FloatRect{{m_zone.left + width, m_zone.top + height},
                                                        {width, height}},
                                          m_capacity);
            std::vector<Holder> holders;
            for (auto &holder : m_holders)
            {
                if (m_topLeft->hasZone(holder.trace->getBounds()))
                {
                    m_topLeft->append(holder);
                    continue;
                }
                if (m_topRight->hasZone(holder.trace->getBounds()))
                {
                    m_topRight->append(holder);
                    continue;
                }
                if (m_bottomLeft->hasZone(holder.trace->getBounds()))
                {
                    m_bottomLeft->append(holder);
                    continue;
                }
                if (m_bottomRight->hasZone(holder.trace->getBounds()))
                {
                    m_bottomRight->append(holder);
                    continue;
                }
                holders.push_back(holder);
            }
            m_holders = std::move(holders);
            m_subdimensions = true;
        }
    }

    void Dimension::collisions(const Holder &holder)
    {
        for (auto &_holder : m_holders)
        {
            if (holder.trace->checkCollision(*_holder.trace))
            {
                holder.body->collision(*_holder.body);
                _holder.body->collision(*holder.body);
            }
        }
    }

    void Dimension::collisionsChildren(const Holder &holder)
    {
        if (m_subdimensions)
        {
            m_topLeft->collisions(holder);
            m_topLeft->collisionsChildren(holder);

            m_topRight->collisions(holder);
            m_topRight->collisionsChildren(holder);

            m_bottomLeft->collisions(holder);
            m_bottomLeft->collisionsChildren(holder);

            m_bottomRight->collisions(holder);
            m_bottomRight->collisionsChildren(holder);
        }
    }

    Dimension &Dimension::locateCollisions(Dimension &dimension, const Holder &holder)
    {
        auto *_dimension = &dimension;
        auto *targetDimension = &dimension;
        while (_dimension)
        {
            targetDimension = _dimension;
            _dimension->collisions(holder);
            _dimension = _dimension->locate(holder.trace->getBounds());
        }
        targetDimension->collisionsChildren(holder);
        return *targetDimension;
    }

}