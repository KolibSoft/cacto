#ifndef CACTO_TRACE_VIEWER_HPP
#define CACTO_TRACE_VIEWER_HPP

#include <Cacto/Graphics/Rectangle.hpp>
#include <Cacto/Graphics/LineViewer.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace cacto
{

    class Trace;

    class CACTO_PHYSICS_API TraceViewer
        : public virtual sf::Drawable
    {

    public:
        const Trace *const getTrace() const;
        void setTrace(const Trace *const value);

        TraceViewer();
        virtual ~TraceViewer();

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        const Trace *m_trace;

        mutable Rectangle m_bounds;
        mutable LineViewer m_boundsViewer;
        mutable LineViewer m_geometryViewer;
    };

}

#endif