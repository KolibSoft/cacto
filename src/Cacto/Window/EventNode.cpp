#include <Cacto/Window/EventNode.hpp>

namespace cacto
{

    void EventNode::dispatch(const sf::Event &event)
    {
        EventNode::dispatch(*this, event);
    }

    void EventNode::event(const sf::Event &event)
    {
        EventNode::event(*this, event);
    }

    void EventNode::bubble(Node &target, const sf::Event &event)
    {
        EventNode::bubble(*this, target, event);
    }

    EventNode::EventNode() = default;

    EventNode::~EventNode() = default;

    bool EventNode::dispatch(Node &node, const sf::Event &event)
    {
        auto nodeEvent = dynamic_cast<EventNode *>(&node);
        auto handled = nodeEvent && nodeEvent->onDispatch(event);
        if (!handled)
        {
            auto childCount = node.getChildCount();
            for (szt i = 0; i < childCount; i++)
            {
                auto child = node.getChild(i);
                handled = EventNode::dispatch(*child, event);
                if (handled)
                    break;
            }
            // Capture Event Here
        }
        return handled;
    }

    bool EventNode::event(Node &node, const sf::Event &event)
    {
        auto nodeEvent = dynamic_cast<EventNode *>(&node);
        auto handled = nodeEvent && nodeEvent->onEvent(event);
        return handled;
    }

    bool EventNode::bubble(Node &node, Node &target, const sf::Event &event)
    {
        auto nodeEvent = dynamic_cast<EventNode *>(&node);
        auto handled = nodeEvent && nodeEvent->onBubble(target, event);
        if (!handled)
        {
            auto parent = node.getParent();
            handled = parent && EventNode::bubble(*parent, target, event);
        }
        return handled;
    }

    bool EventNode::onDispatch(const sf::Event &event)
    {
        return false;
    }

    bool EventNode::onEvent(const sf::Event &event)
    {
        return false;
    }

    bool EventNode::onBubble(Node &target, const sf::Event &event)
    {
        return false;
    }

}