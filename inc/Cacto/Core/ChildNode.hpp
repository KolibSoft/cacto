#pragma once

#include <Cacto/Core/Node.hpp>

namespace cacto
{

    class ParentNode;

    class ChildNode
        : public virtual Node
    {

    public:
        virtual void attach(ParentNode &child) = 0;
        virtual void detach() = 0;

        ChildNode() = default;
        virtual ~ChildNode() = default;
    };

}