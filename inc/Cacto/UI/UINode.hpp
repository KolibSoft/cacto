#ifndef CACTO_UI_NODE_HPP
#define CACTO_UI_NODE_HPP

#include <Cacto/Graphics/DrawNode.hpp>
#include <Cacto/Window/EventNode.hpp>
#include <Cacto/UI/InflatableNode.hpp>

namespace cacto
{

    class UINode
        : public virtual DrawNode,
          public virtual InflatableNode,
          public virtual EventNode
    {

    public:
        UINode() = default;
        virtual ~UINode() = default;
    };

}

#endif