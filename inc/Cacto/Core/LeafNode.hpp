#pragma once

#include <Cacto/Core/Node.hpp>

namespace cacto
{

    class CACTO_CORE_API LeafNode
        : public virtual Node
    {

    public:
        szt getChildCount() const override;
        Shared<Node> getChild(szt index = 0) const override;

        LeafNode() = default;
        virtual ~LeafNode() = default;

    protected:
        void onAppend(const Shared<Node> &child) override;
        void onRemove(const Shared<Node> &child) override;
    };

}
