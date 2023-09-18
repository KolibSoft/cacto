#ifndef CACTO_EVENT_NODE_HPP
#define CACTO_EVENT_NODE_HPP

#include <Cacto/Core/Node.hpp>
#include <Cacto/Window/Export.hpp>

namespace sf
{
    class Event;
}

namespace cacto
{

    class EventSignal;

    class CACTO_WINDOW_API EventNode
        : public virtual Node
    {

    public:
        bool handleSignal(Node *const target, const Signal &signal) override;
        void event(const sf::Event &event);

        EventNode();
        virtual ~EventNode();

    protected:
        virtual void onEvent(const EventSignal &signal);
    };

}

#endif