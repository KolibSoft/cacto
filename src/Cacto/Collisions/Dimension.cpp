#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Graphics/Rectangle.hpp>
#include <Cacto/Collisions/Body.hpp>
#include <Cacto/Collisions/Dimension.hpp>

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
                return m_topLeft.get();
            if (m_topRight->hasZone(zone))
                return m_topRight.get();
            if (m_bottomRight->hasZone(zone))
                return m_bottomRight.get();
            if (m_bottomRight->hasZone(zone))
                return m_bottomRight.get();
        }
        return nullptr;
    }

    void Dimension::append(Body &body, const Trace &trace)
    {
        append(Holder{&body, &trace});
    }

    void Dimension::collisions(Body &body, const Trace &trace)
    {
        collisions(Holder{&body, &trace});
    }

    void Dimension::collisionsChildren(Body &body, const Trace &trace)
    {
        collisionsChildren(Holder{&body, &trace});
    }

    Dimension &Dimension::locateCollisions(Body &body, const Trace &trace)
    {
        auto &target = Dimension::locateCollisions(*this, Holder{&body, &trace});
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
                m_topLeft.reset();
                m_topRight.reset();
                m_bottomLeft.reset();
                m_bottomRight.reset();
                m_subdimensions = false;
            }
        }
    }

    Dimension::Dimension(const sf::FloatRect &zone, szt capacity)
        : m_zone(zone), m_capacity(capacity), m_holders(), m_subdimensions(false),
          m_topLeft(nullptr), m_topRight(nullptr),
          m_bottomLeft(nullptr), m_bottomRight(nullptr)
    {
        if (capacity < 1)
            capacity = 1;
    }

    Dimension::~Dimension() = default;

    void Dimension::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        sf::VertexArray array(sf::PrimitiveType::LineStrip);
        setPoints(array, Rectangle({m_zone.left, m_zone.top}, {m_zone.width, m_zone.height}));
        setColor(array, sf::Color::Magenta);
        array.append(array[0]);
        target.draw(array, states);
        if (m_subdimensions)
        {
            m_topLeft->draw(target, states);
            m_topRight->draw(target, states);
            m_bottomLeft->draw(target, states);
            m_bottomRight->draw(target, states);
        }
        for (auto &holder : m_holders)
        {
            auto bounds = holder.trace->getBounds();
            setPoints(array, Rectangle({bounds.left, bounds.top}, {bounds.width, bounds.height}));
            setColor(array, sf::Color::Blue);
            array.append(array[0]);
            target.draw(array, states);

            auto _states = states;
            setPoints(array, *holder.trace->getGeometry());
            setColor(array, sf::Color::Red);
            array.append(array[0]);
            _states.transform *= holder.trace->getTransform();
            target.draw(array, _states);
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
            m_topLeft.reset(new Dimension(sf::FloatRect{{m_zone.left, m_zone.top},
                                                        {width, height}},
                                          m_capacity));
            m_topRight.reset(new Dimension(sf::FloatRect{{m_zone.left + width, m_zone.top},
                                                         {width, height}},
                                           m_capacity));
            m_bottomLeft.reset(new Dimension(sf::FloatRect{{m_zone.left, m_zone.top + height},
                                                           {width, height}},
                                             m_capacity));
            m_bottomRight.reset(new Dimension(sf::FloatRect{{m_zone.left + width, m_zone.top + height},
                                                            {width, height}},
                                              m_capacity));
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