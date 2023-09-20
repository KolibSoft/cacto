#include <Cacto/Animations/UpdateNode.hpp>

namespace cacto
{

    void UpdateNode::update(const sf::Time &time)
    {
        onUpdate(time);
    }

    UpdateNode::UpdateNode() = default;

    UpdateNode::~UpdateNode() = default;

    void UpdateNode::update(Node &node, const sf::Time &time)
    {
        auto updateNode = dynamic_cast<UpdateNode *>(&node);
        if (updateNode)
            updateNode->onUpdate(time);
        auto childCount = node.getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = node.getChild(i);
            UpdateNode::update(*child, time);
        }
    }

    void UpdateNode::onUpdate(const sf::Time &time)
    {
    }

}