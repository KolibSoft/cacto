#include <Cacto/Collisions/CollisionNode.hpp>

namespace cacto
{

    void CollisionNode::collision(Dimension &dimension, const sf::Transform &tranform)
    {
        CollisionNode::collision(*this, dimension, tranform);
    }

    void CollisionNode::collision(Node &node, Dimension &dimension, const sf::Transform &tranform)
    {
        auto collisionNode = dynamic_cast<CollisionNode *>(&node);
        auto handled = collisionNode && collisionNode->onCollision(dimension, tranform);
        if (!handled)
        {
            auto childCount = node.getChildCount();
            for (szt i = 0; i < childCount; i++)
            {
                auto child = node.getChild(i);
                CollisionNode::collision(*child, dimension, tranform);
            }
        }
    }

    CollisionNode::CollisionNode() = default;

    CollisionNode::~CollisionNode() = default;

    bool CollisionNode::onCollision(Dimension &dimension, const sf::Transform &tranform)
    {
        return false;
    }

}