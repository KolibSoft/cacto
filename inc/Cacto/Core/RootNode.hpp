#ifndef CACTO_ROOT_NODE_HPP
#define CACTO_ROOT_NODE_HPP

#include <Cacto/Core/Node.hpp>

namespace cacto
{

    class CACTO_CORE_API RootNode
        : public virtual Node
    {

    public:
        Node *const getParent() const override;

        RootNode();
        virtual ~RootNode();

    protected:
        void onAttach(Node &parent) override;
        void onDetach(Node &parent) override;
    };

}

#endif