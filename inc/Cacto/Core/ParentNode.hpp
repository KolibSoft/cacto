#pragma once

#include <Cacto/Core/Node.hpp>

namespace cacto
{

    class ChildNode;

    class CACTO_CORE_API ParentNode
        : public virtual Node
    {

    public:
        ParentNode *const getParent() const override;

        virtual void append(ChildNode &child) = 0;
        virtual void remove(ChildNode &child) = 0;

        ParentNode() = default;
        virtual ~ParentNode() = default;
    };

}