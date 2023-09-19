#ifndef CACTO_GENERIC_NODE_HPP
#define CACTO_GENERIC_NODE_HPP

#include <vector>
#include <Cacto/Core/Node.hpp>

namespace cacto
{

    class CACTO_CORE_API GenericNode
        : public virtual Node
    {

    public:
        Node *const getParent() const override;

        szt getChildCount() const override;
        SharedNode getChild(szt index = 0) const override;

        void attach(Node *const parent) override;
        void detach(Node *const parent) override;

        void append(const SharedNode &child) override;
        void remove(const SharedNode &child) override;

        GenericNode();
        virtual ~GenericNode();

    private:
        Node *m_parent;
        std::vector<SharedNode> m_children;
    };

}

#endif