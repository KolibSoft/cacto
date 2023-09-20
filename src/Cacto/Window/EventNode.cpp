#include <Cacto/Window/EventNode.hpp>

namespace cacto
{

    void EventNode::event(const sf::Event &event)
    {
        onEvent(event);
    }

    EventNode::EventNode() = default;

    EventNode::~EventNode() = default;

    bool EventNode::event(Node &node, const sf::Event &event)
    {
        auto childCount = node.getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = node.getChild(i);
            auto handled = EventNode::event(*child, event);
            if (handled)
                return true;
        }
        auto eventNode = dynamic_cast<EventNode *>(&node);
        auto handled = eventNode && eventNode->onEvent(event);
        return handled;
    }

    bool EventNode::onEvent(const sf::Event &event)
    {
        return false;
    }

}