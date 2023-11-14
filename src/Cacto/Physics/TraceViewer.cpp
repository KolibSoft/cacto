#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/Physics/Trace.hpp>
#include <Cacto/Physics/TraceViewer.hpp>

namespace cacto
{

    const Trace *const TraceViewer::getTrace() const
    {
        return m_trace;
    }

    void TraceViewer::setTrace(const Trace *const value)
    {
        m_trace = value;
        auto bounds = m_trace->getBounds();
        m_bounds = {{bounds.left, bounds.top}, {bounds.width, bounds.height}};
        m_boundsViewer.setLine(&m_bounds);
        m_geometryViewer.setLine(&m_trace->getGeometry());
    }

    TraceViewer::TraceViewer()
        : m_trace(nullptr),
          m_bounds(),
          m_boundsViewer(),
          m_geometryViewer()
    {
        m_boundsViewer.setColor(sf::Color::Blue);
        m_boundsViewer.setClosed(true);
        m_geometryViewer.setColor(sf::Color::Red);
        m_geometryViewer.setClosed(true);
    }

    TraceViewer::~TraceViewer() = default;

    void TraceViewer::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (m_trace)
        {
            target.draw(m_boundsViewer, states);
            auto _states = states;
            _states.transform = m_trace->getTransform();
            target.draw(m_geometryViewer, _states);
        }
    }

}