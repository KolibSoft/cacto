#ifndef CACTO_LEAF_NODE_HPP
#define CACTO_LEAF_NODE_HPP

#include <Cacto/Core/Node.hpp>

namespace cacto
{

    class CACTO_CORE_API LeafNode
        : public virtual Node
    {

    public:
        szt getChildCount() const override;
        SharedNode getChild(szt index = 0) const override;

        LeafNode();
        virtual ~LeafNode();

    protected:
        void onAppend(const SharedNode &child) override;
        void onRemove(const SharedNode &child) override;
    };

}

#endif