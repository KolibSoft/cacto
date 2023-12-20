#pragma once

#include <Cacto/Core/Node.hpp>

namespace cacto
{

    class CACTO_CORE_API RootNode
        : public virtual Node
    {

    public:
        Shared<Node> getParent() const override;

        RootNode() = default;
        virtual ~RootNode() = default;

    protected:
        void onAttach(const Shared<Node> &parent) override;
        void onDetach(const Shared<Node> &parent) override;
    };

}
