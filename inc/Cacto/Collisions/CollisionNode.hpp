#ifndef CACTO_COLLISION_NODE_HPP
#define CACTO_COLLISION_NODE_HPP

#include <Cacto/Core/Node.hpp>
#include <Cacto/Collisions/Export.hpp>

namespace cacto
{

    class Dimension;

    class CACTO_COLLISIONS_API CollisionNode
        : public virtual Node
    {

    public:
        void collision(Dimension &dimension);

        CollisionNode();
        virtual ~CollisionNode();

        static void collision(Node &node, Dimension &dimension);

    protected:
        virtual bool onCollision(Dimension &dimension);
    };

}

#endif