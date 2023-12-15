#pragma once

#include <Cacto/Core/Node.hpp>

namespace cacto
{

    class CACTO_CORE_API RootNode
        : public virtual Node
    {

    public:
        Node *const getParent() const override;

        RootNode() = default;
        virtual ~RootNode() = default;

    protected:
        void onAttach(Node &parent) override;
        void onDetach(Node &parent) override;
    };

}
