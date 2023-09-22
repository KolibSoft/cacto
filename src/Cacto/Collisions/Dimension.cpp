#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Graphics/Rectangle.hpp>
#include <Cacto/Collisions/Body.hpp>
#include <Cacto/Collisions/Dimension.hpp>

namespace cacto
{

    const std::vector<Dimension::Trace> &Dimension::getTraces() const
    {
        return m_traces;
    }

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

    void Dimension::append(const Trace &trace)
    {
        m_traces.push_back(trace);
        if (m_traces.size() > 2)
            split();
    }

    void Dimension::collisions(const Trace &trace, bool subdimensions)
    {
        for (auto &_trace : m_traces)
        {
            if (zoneWith(trace.zone, _trace.zone) && trace.body->checkCollision(*_trace.body))
            {
                trace.body->collision(*_trace.body);
                _trace.body->collision(*trace.body);
            }
        }
        if (subdimensions && m_subdimensions)
        {
            m_topLeft->collisions(trace, true);
            m_topRight->collisions(trace, true);
            m_bottomLeft->collisions(trace, true);
            m_bottomRight->collisions(trace, true);
        }
    }

    void Dimension::collisions(Body &body)
    {
        Trace trace{&body, body.getBounds()};
        auto &target = Dimension::collisions(*this, trace);
        target.append(trace);
    }

    Dimension::Dimension(const sf::FloatRect &zone)
        : m_zone(zone), m_traces(), m_subdimensions(false),
          m_topLeft(nullptr), m_topRight(nullptr),
          m_bottomLeft(nullptr), m_bottomRight(nullptr)
    {
    }

    Dimension::~Dimension() = default;

    Dimension &Dimension::collisions(Dimension &dimension, const Trace &trace)
    {
        auto *_dimension = &dimension;
        auto *targetDimension = &dimension;
        while (_dimension)
        {
            targetDimension = _dimension;
            _dimension->collisions(trace, false);
            _dimension = _dimension->locate(trace.zone);
        }
        targetDimension->collisions(trace, true);
        return *targetDimension;
    }

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
        for (auto &trace : m_traces)
        {
            setPoints(array, Rectangle({trace.zone.left, trace.zone.top}, {trace.zone.width, trace.zone.height}));
            setColor(array, sf::Color::Blue);
            array.append(array[0]);
            target.draw(array, states);

            auto _states = states;
            setPoints(array, *trace.body->getGeometry());
            setColor(array, sf::Color::Red);
            array.append(array[0]);
            _states.transform *= trace.body->getTransform();
            target.draw(array, _states);
        }
    }

    void Dimension::split()
    {
        if (!m_subdimensions)
        {
            auto width = m_zone.width / 2;
            auto height = m_zone.height / 2;
            m_topLeft.reset(new Dimension(sf::FloatRect{{m_zone.left, m_zone.top},
                                                        {width, height}}));
            m_topRight.reset(new Dimension(sf::FloatRect{{m_zone.left + width, m_zone.top},
                                                         {width, height}}));
            m_bottomLeft.reset(new Dimension(sf::FloatRect{{m_zone.left, m_zone.top + height},
                                                           {width, height}}));
            m_bottomRight.reset(new Dimension(sf::FloatRect{{m_zone.left + width, m_zone.top + height},
                                                            {width, height}}));
            std::vector<Trace> traces;
            for (auto &trace : m_traces)
            {
                if (m_topLeft->hasZone(trace.zone))
                {
                    m_topLeft->append(trace);
                    continue;
                }
                if (m_topRight->hasZone(trace.zone))
                {
                    m_topRight->append(trace);
                    continue;
                }
                if (m_bottomLeft->hasZone(trace.zone))
                {
                    m_bottomLeft->append(trace);
                    continue;
                }
                if (m_bottomRight->hasZone(trace.zone))
                {
                    m_bottomRight->append(trace);
                    continue;
                }
                traces.push_back(trace);
            }
            m_traces = std::move(traces);
            m_subdimensions = true;
        }
    }

}