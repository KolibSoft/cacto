#include <Cacto/Graphics/Utils.hpp>
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

    Dimension &Dimension::collisions(Body &body)
    {
        auto &target = Dimension::collisions(*this, body);
        return target;
    }

    Dimension::Dimension(const sf::FloatRect &zone)
        : m_zone(zone), m_traces(), m_subdimensions(false),
          m_topLeft(nullptr), m_topRight(nullptr),
          m_bottomLeft(nullptr), m_bottomRight(nullptr)
    {
    }

    Dimension::~Dimension() = default;

    Dimension &Dimension::collisions(Dimension &dimension, Body &body)
    {
        auto zone = body.getBounds();
        auto *_dimension = &dimension;
        auto *targetDimension = &dimension;
        while (_dimension)
        {
            targetDimension = _dimension;
            for (auto &trace : _dimension->getTraces())
            {
                if (zoneWith(zone, trace.zone))
                {
                    body.collision(*trace.body);
                    trace.body->collision(body);
                }
            }
            _dimension = _dimension->locate(zone);
        }
        return *targetDimension;
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
                m_traces.push_back(trace);
            }
            m_traces = std::move(traces);
            m_subdimensions = true;
        }
    }

}