#ifndef CACTO_ROOT_NODE_HPP
#define CACTO_ROOT_NODE_HPP

#include <Cacto/Core/Node.hpp>

namespace cacto
{

    class CACTO_CORE_API RootNode
        : public virtual Node
    {

    public:
        SharedNode getParent() const override;

        RootNode();
        virtual ~RootNode();

    protected:
        void onAttach(const SharedNode &child) override;
        void onDetach(const SharedNode &child) override;
    };

}

#endif