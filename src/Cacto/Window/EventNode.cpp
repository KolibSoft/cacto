#include <Cacto/Window/EventSignal.hpp>
#include <Cacto/Window/EventNode.hpp>

namespace cacto
{

    bool EventNode::handleSignal(Node &target, const Signal &signal)
    {
        auto *eventSignal = dynamic_cast<const EventSignal *>(&signal);
        auto handled = eventSignal && onEvent(target, *eventSignal);
        return handled;
    }

    void EventNode::event(const sf::Event &event)
    {
        EventSignal signal{event};
        onEvent(*this, signal);
    }

    bool EventNode::onEvent(Node &target, const EventSignal &signal)
    {
        auto handled = &target == this ? Node::dispatchSignal(signal) : Node::bubbleSignal(target, signal);
        return handled;
    }

    EventNode::EventNode() = default;

    EventNode::~EventNode() = default;

}