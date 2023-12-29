#include <Cacto/Core/Node.hpp>
#include <Cacto/Animations/Updatable.hpp>
#include <Cacto/Animations/NodeUtils.hpp>

namespace cacto
{

    void update(Node &node, const sf::Time &time)
    {
        auto updateNode = dynamic_cast<Updatable *>(&node);
        if (updateNode)
            updateNode->update(time);
        else
            updateChildren(node, time);
    }

    void updateChildren(const Node &node, const sf::Time &time)
    {
        auto childCount = node.getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = node.getChild(i);
            if (child)
                update(*child, time);
        }
    }

}