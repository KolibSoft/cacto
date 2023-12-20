#include <Cacto/Window/EventNode.hpp>

namespace cacto
{

    bool EventNode::event(const sf::Event &event)
    {
        auto handled = onEvent(event);
        return handled;
    }

    bool EventNode::bubble(const Shared<Node> &target, const sf::Event &event)
    {
        auto handled = onBubble(target, event);
        return handled;
    }

    EventNode::EventNode() = default;

    EventNode::~EventNode() = default;

    bool EventNode::event(const Shared<Node> &node, const sf::Event &event)
    {
        if (node == nullptr)
            throw std::runtime_error("The node was null");
        auto eventNode = std::dynamic_pointer_cast<EventNode>(node);
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

    bool EventNode::eventChildren(const Shared<Node> &node, const sf::Event &event)
    {
        if (node == nullptr)
            throw std::runtime_error("The node was null");
        auto childCount = node->getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = node->getChild(i);
            auto handled = child && EventNode::event(child, event);
            if (handled)
                return handled;
        }
        return false;
    }

    bool EventNode::bubble(const Shared<Node> &node, const Shared<Node> &target, const sf::Event &event)
    {
        if (node == nullptr)
            throw std::runtime_error("The node was null");
        auto eventNode = std::dynamic_pointer_cast<EventNode>(node);
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

    bool EventNode::bubbleParent(const Shared<Node> &node, const Shared<Node> &target, const sf::Event &event)
    {
        if (node == nullptr)
            throw std::runtime_error("The node was null");
        auto parent = node->getParent();
        auto handled = parent && EventNode::bubble(parent, target, event);
        return handled;
    }

    bool EventNode::eventChildren(const sf::Event &event)
    {
        auto childCount = getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = getChild(i);
            auto handled = child && EventNode::event(child, event);
            if (handled)
                return handled;
        }
        return false;
    }

    bool EventNode::bubbleParent(const Shared<Node> &target, const sf::Event &event)
    {
        auto parent = getParent();
        auto handled = parent && EventNode::bubble(parent, target, event);
        return handled;
    }

    bool EventNode::onEvent(const sf::Event &event)
    {
        auto handled = eventChildren(event);
        return handled;
    }

    bool EventNode::onBubble(const Shared<Node> &target, const sf::Event &event)
    {
        auto handled = bubbleParent(target, event);
        return handled;
    }

}