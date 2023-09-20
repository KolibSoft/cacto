#ifndef CACTO_LEAFT_NODE_HPP
#define CACTO_LEAFT_NODE_HPP

#include <Cacto/Core/Node.hpp>

namespace cacto
{

    class CACTO_CORE_API LeafNode
        : public virtual Node
    {

    public:
        void append(const SharedNode &child) override;
        void remove(const SharedNode &child) override;

        LeafNode();
        virtual ~LeafNode();
    };

}

#endif