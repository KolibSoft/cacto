#include <Cacto/Animations/UpdateNode.hpp>

namespace cacto
{

    void UpdateNode::update(const sf::Time &time)
    {
        updateChildren(time);
    }

    void UpdateNode::updateChildren(const sf::Time &time) const
    {
        UpdateNode::updateChildren(*this, time);
    }

    UpdateNode::UpdateNode() = default;

    UpdateNode::~UpdateNode() = default;

    void UpdateNode::update(Node &node, const sf::Time &time)
    {
        auto updateNode = dynamic_cast<UpdateNode *>(&node);
        if (updateNode)
            updateNode->update(time);
        else
            UpdateNode::updateChildren(node, time);
    }

    void UpdateNode::updateChildren(const Node &node, const sf::Time &time)
    {
        auto childCount = node.getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = node.getChild(i);
            if (child)
                UpdateNode::update(*child, time);
        }
    }

}