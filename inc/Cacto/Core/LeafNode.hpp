#ifndef CACTO_LEAFT_NODE_HPP
#define CACTO_LEAFT_NODE_HPP

#include <Cacto/Core/Node.hpp>

namespace cacto
{

    class CACTO_CORE_API LeafNode
        : public virtual Node
    {

    public:
        LeafNode();
        virtual ~LeafNode();

    protected:
        void onAppend(const SharedNode &child) override;
        void onRemove(const SharedNode &child) override;
    };

}

#endif