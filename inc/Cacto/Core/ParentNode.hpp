#pragma once

#include <Cacto/Core/Node.hpp>

namespace cacto
{

    class ChildNode;

    class CACTO_CORE_API ParentNode
        : public virtual Node
    {

    public:
        Node *const getParent() const override;
        void clearChildren();

        virtual void append(ChildNode &child) = 0;
        virtual void remove(ChildNode &child) = 0;

        ParentNode() = default;
        virtual ~ParentNode() = default;
    };

}