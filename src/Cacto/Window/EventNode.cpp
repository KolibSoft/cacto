#include <Cacto/Window/EventNode.hpp>

namespace cacto
{

    bool EventNode::event(const sf::Event &event)
    {
        auto handled = eventChildren(event);
        return handled;
    }

    bool EventNode::eventChildren(const sf::Event &event) const
    {
        auto handled = EventNode::eventChildren(*this, event);
        return false;
    }

    bool EventNode::bubble(Node &target, const sf::Event &event)
    {
        auto handled = bubbleParent(target, event);
        return handled;
    }

    bool EventNode::bubbleParent(Node &target, const sf::Event &event) const
    {
        auto handled = EventNode::bubbleParent(*this, target, event);
        return false;
    }

    EventNode::EventNode() = default;

    EventNode::~EventNode() = default;

    bool EventNode::event(Node &node, const sf::Event &event)
    {
        auto eventNode = dynamic_cast<EventNode *>(&node);
        if (eventNode)
        {
            auto handled = eventNode->event(event);
            return handled;
        }
        else
        {
            auto handled = EventNode::eventChildren(node, event);
            return handled;
        }
    }

    bool EventNode::eventChildren(const Node &node, const sf::Event &event)
    {
        auto childCount = node.getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = node.getChild(i);
            auto handled = child && EventNode::event(*child, event);
            if (handled)
                return handled;
        }
        return false;
    }

    bool EventNode::bubble(Node &node, Node &target, const sf::Event &event)
    {
        auto eventNode = dynamic_cast<EventNode *>(&node);
        if (eventNode)
        {
            auto handled = eventNode->bubble(target, event);
            return handled;
        }
        else
        {
            auto handled = EventNode::bubbleParent(node, target, event);
            return handled;
        }
    }

    bool EventNode::bubbleParent(const Node &node, Node &target, const sf::Event &event)
    {
        auto parent = node.getParent();
        auto handled = parent && EventNode::bubble(*parent, target, event);
        return handled;
    }

}