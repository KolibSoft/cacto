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
        Node *const getChild(szt index = 0) const override;

        LeafNode() = default;
        virtual ~LeafNode() = default;

    protected:
        void onAppend(Node &child) override;
        void onRemove(Node &child) override;
    };

}

#endif