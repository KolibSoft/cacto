#ifndef CACTO_GENERIC_NODE_HPP
#define CACTO_GENERIC_NODE_HPP

#include <vector>
#include <Cacto/Core/Node.hpp>
#include <Cacto/Graphics/DrawNode.hpp>
#include <Cacto/Window/EventNode.hpp>
#include <Cacto/Animations/UpdateNode.hpp>
#include <Cacto/Common/Export.hpp>

namespace cacto
{

    class CACTO_COMMON_API GenericNode
        : public virtual DrawNode,
          public virtual EventNode,
          public virtual UpdateNode
    {

    public:
        Node *const getParent() const override;

        szt getChildCount() const override;
        SharedNode getChild(szt index = 0) const override;

        void append(const SharedNode &child);
        void remove(const SharedNode &child);

        GenericNode();
        virtual ~GenericNode();

    protected:
        void onAppend(const SharedNode &child) override;
        void onRemove(const SharedNode &child) override;

        void onAttach(Node &parent) override;
        void onDetach(Node &parent) override;

    private:
        Node *m_parent;
        std::vector<SharedNode> m_children;
    };

}

#endif