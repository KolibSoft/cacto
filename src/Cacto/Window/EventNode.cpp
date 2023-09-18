#include <Cacto/Window/EventSignal.hpp>
#include <Cacto/Window/EventNode.hpp>

namespace cacto
{

    bool EventNode::handleSignal(Node *const target, const Signal &signal)
    {
        if (!target)
        {
            auto *eventSignal = dynamic_cast<const EventSignal *>(&signal);
            if (eventSignal)
            {
                onEvent(*eventSignal);
                return true;
            }
        }
        return false;
    }

    void EventNode::event(const sf::Event &event)
    {
        EventSignal signal{event};
        onEvent(signal);
    }

    void EventNode::onEvent(const EventSignal &signal)
    {
        auto handled = bubbleSignal(this, signal);
    }

}