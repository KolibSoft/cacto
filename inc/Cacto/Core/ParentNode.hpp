#pragma once

#include <Cacto/Core/Node.hpp>

namespace cacto
{

    class ChildNode;

    class ParentNode
        : public virtual Node
    {

    public:
        virtual void append(ChildNode &child) = 0;
        virtual void remove(ChildNode &child) = 0;

        ParentNode() = default;
        virtual ~ParentNode() = default;
    };

}