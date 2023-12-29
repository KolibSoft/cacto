#include <Cacto/Core/Node.hpp>
#include <Cacto/Window/Handler.hpp>
#include <Cacto/Window/NodeUtils.hpp>

namespace cacto
{

    bool handle(Node &node, const sf::Event &event)
    {
        auto eventNode = dynamic_cast<Handler *>(&node);
        if (eventNode)
        {
            auto handled = eventNode->handle(event);
            return handled;
        }
        else
        {
            auto handled = handleChildren(node, event);
            return handled;
        }
    }

    bool handleChildren(const Node &node, const sf::Event &event)
    {
        auto childCount = node.getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = node.getChild(i);
            auto handled = child && handle(*child, event);
            if (handled)
                return handled;
        }
        return false;
    }

    bool bubble(Node &node, Node &target, const sf::Event &event)
    {
        auto eventNode = dynamic_cast<Handler *>(&node);
        if (eventNode)
        {
            auto handled = eventNode->bubble(target, event);
            return handled;
        }
        else
        {
            auto handled = bubbleParent(node, target, event);
            return handled;
        }
    }

    bool bubbleParent(const Node &node, Node &target, const sf::Event &event)
    {
        auto parent = node.getParent();
        auto handled = parent && bubble(*parent, target, event);
        return handled;
    }

}