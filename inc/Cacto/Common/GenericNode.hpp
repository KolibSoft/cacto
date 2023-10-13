#ifndef CACTO_GENERIC_NODE_HPP
#define CACTO_GENERIC_NODE_HPP

#include <vector>
#include <Cacto/Core/Object.hpp>
#include <Cacto/Core/Node.hpp>
#include <Cacto/Graphics/DrawNode.hpp>
#include <Cacto/Window/EventNode.hpp>
#include <Cacto/UI/InflatableNode.hpp>
#include <Cacto/Animations/UpdateNode.hpp>
#include <Cacto/Collisions/CollisionNode.hpp>
#include <Cacto/Common/Export.hpp>

namespace cacto
{

    using WeakNode = std::weak_ptr<Node>;

    class CACTO_COMMON_API GenericNode
        : public Object,
          public virtual DrawNode,
          public virtual EventNode,
          public virtual InflatableNode,
          public virtual UpdateNode,
          public virtual CollisionNode
    {

    public:
        SharedNode getParent() const override;

        szt getChildCount() const override;
        SharedNode getChild(szt index = 0) const override;

        void append(const SharedNode &child);
        void remove(const SharedNode &child);

        void attach(const SharedNode &parent);
        void detach(const SharedNode &parent);

        GenericNode();
        virtual ~GenericNode();

    protected:
        void onAppend(const SharedNode &child) override;
        void onRemove(const SharedNode &child) override;

        void onAttach(const SharedNode &parent) override;
        void onDetach(const SharedNode &parent) override;

    private:
        WeakNode m_parent;
        std::vector<SharedNode> m_children;
    };

}

#endif