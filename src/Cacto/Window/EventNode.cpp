#include <Cacto/Window/EventNode.hpp>

namespace cacto
{

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

    bool EventNode::event(Node &node, const sf::Event &event)
    {
        auto eventNode = dynamic_cast<EventNode *>(&node);
        if (eventNode)
        {
            auto handled = eventNode->onEvent(event);
            return handled;
        }
        else
        {
            auto handled = EventNode::eventChildren(node, event);
            return handled;
        }
    }

    bool EventNode::eventChildren(Node &node, const sf::Event &event)
    {
        auto handled = false;
        auto childCount = node.getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = node.getChild(i);
            auto handled = child && EventNode::event(*child, event);
            if (handled)
                break;
        }
        return handled;
    }

    bool EventNode::bubble(Node &node, Node &target, const sf::Event &event)
    {
        auto eventNode = dynamic_cast<EventNode *>(&node);
        if (eventNode)
        {
            auto handled = eventNode->onBubble(target, event);
            return handled;
        }
        else
        {
            auto handled = EventNode::bubbleParent(node, target, event);
            return handled;
        }
    }

    bool EventNode::bubbleParent(Node &node, Node &target, const sf::Event &event)
    {
        auto parent = node.getParent();
        auto handled = parent && EventNode::bubble(node, target, event);
        return handled;
    }

    bool EventNode::eventChildren(const sf::Event &event)
    {
        auto handled = EventNode::eventChildren(*this, event);
        return handled;
    }

    bool EventNode::bubbleParent(Node &target, const sf::Event &event)
    {
        auto handled = EventNode::bubbleParent(*this, target, event);
        return handled;
    }

    bool EventNode::onEvent(const sf::Event &event)
    {
        auto handled = eventChildren(event);
        return handled;
    }

    bool EventNode::onBubble(Node &target, const sf::Event &event)
    {
        auto handled = bubbleParent(target, event);
        return handled;
    }

}