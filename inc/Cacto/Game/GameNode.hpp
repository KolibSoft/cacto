#ifndef CACTO_GENERIC_NODE_HPP
#define CACTO_GENERIC_NODE_HPP

#include <vector>
#include <Cacto/Core/Node.hpp>
#include <Cacto/Graphics/DrawNode.hpp>
#include <Cacto/Window/EventNode.hpp>
#include <Cacto/UI/InflatableNode.hpp>
#include <Cacto/Animations/UpdateNode.hpp>
#include <Cacto/Physics/CollisionNode.hpp>
#include <Cacto/Game/Export.hpp>

namespace cacto
{

    class CACTO_GAME_API GameNode
        : public virtual DrawNode,
          public virtual EventNode,
          public virtual InflatableNode,
          public virtual UpdateNode,
          public virtual CollisionNode
    {

    public:
        Node *const getParent() const override;

        szt getChildCount() const override;
        Node *const getChild(szt index = 0) const override;

        void append(Node &child);
        void remove(Node &child);

        GameNode();
        virtual ~GameNode();

    protected:
        void onAppend(Node &child) override;
        void onRemove(Node &child) override;

        void onAttach(Node &parent) override;
        void onDetach(Node &parent) override;

    private:
        Node *m_parent;
        std::vector<Node *> m_children;
    };

}

#endif