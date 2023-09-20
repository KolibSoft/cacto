#include <Cacto/Collisions/CollisionNode.hpp>

namespace cacto
{

    void CollisionNode::collision(Dimension &dimension)
    {
        CollisionNode::collision(*this, dimension);
    }

    void CollisionNode::collision(Node &node, Dimension &dimension)
    {
        auto collisionNode = dynamic_cast<CollisionNode *>(&node);
        auto handled = collisionNode && collisionNode->onCollision(dimension);
        if (!handled)
        {
            auto childCount = node.getChildCount();
            for (szt i = 0; i < childCount; i++)
            {
                auto child = node.getChild(i);
                CollisionNode::collision(*child, dimension);
            }
        }
    }

    CollisionNode::CollisionNode() = default;

    CollisionNode::~CollisionNode() = default;

    bool CollisionNode::onCollision(Dimension &dimension)
    {
        return false;
    }

}