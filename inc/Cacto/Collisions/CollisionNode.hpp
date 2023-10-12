#ifndef CACTO_COLLISION_NODE_HPP
#define CACTO_COLLISION_NODE_HPP

#include <SFML/Graphics/Transform.hpp>
#include <Cacto/Core/Node.hpp>
#include <Cacto/Collisions/Export.hpp>

namespace cacto
{

    class Dimension;

    class CACTO_COLLISIONS_API CollisionNode
        : public virtual Node
    {

    public:
        void collision(Dimension &dimension, const sf::Transform &transform = sf::Transform::Identity);

        CollisionNode();
        virtual ~CollisionNode();

        static void collision(Node &node, Dimension &dimension, const sf::Transform &transform = sf::Transform::Identity);

    protected:
        virtual bool onCollision(Dimension &dimension, const sf::Transform &transform = sf::Transform::Identity);
    };

}

#endif