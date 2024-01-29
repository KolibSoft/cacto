#pragma once

#include <Cacto/Core/Node.hpp>

namespace cacto
{

    class ParentNode;

    class CACTO_CORE_API ChildNode
        : public virtual Node
    {

    public:
        szt getChildCount() const override;
        Node *const getChild(szt index = 0) const override;

        virtual void attach(ParentNode &parent) = 0;
        virtual void detach() = 0;

        ChildNode() = default;
        virtual ~ChildNode() = default;
    };

}