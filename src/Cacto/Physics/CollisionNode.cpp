#include <Cacto/Physics/CollisionNode.hpp>

namespace cacto
{

    void CollisionNode::collision(Dimension &dimension, const sf::Transform &tranform)
    {
        CollisionNode::collision(*this, dimension, tranform);
    }

    CollisionNode::CollisionNode() = default;

    CollisionNode::~CollisionNode() = default;

    void CollisionNode::collision(Node &node, Dimension &dimension, const sf::Transform &tranform)
    {
        auto collisionNode = dynamic_cast<CollisionNode *>(&node);
        if (collisionNode)
            collisionNode->onCollision(dimension, tranform);
        else
            CollisionNode::collisionChildren(node, dimension, tranform);
    }

    void CollisionNode::collisionChildren(Node &node, Dimension &dimension, const sf::Transform &tranform)
    {
        auto childCount = node.getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = node.getChild(i);
            CollisionNode::collision(*child, dimension, tranform);
        }
    }

    void CollisionNode::collisionChildren(Dimension &dimension, const sf::Transform &transform)
    {
        CollisionNode::collisionChildren(*this, dimension, transform);
    }

    void CollisionNode::onCollision(Dimension &dimension, const sf::Transform &transform)
    {
        collisionChildren(dimension, transform);
    }

}