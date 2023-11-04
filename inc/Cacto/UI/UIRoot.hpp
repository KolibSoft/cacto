#ifndef CACTO_UI_ROOT_HPP
#define CACTO_UI_ROOT_HPP

#include <Cacto/Core/RootNode.hpp>
#include <Cacto/Graphics/DrawNode.hpp>
#include <Cacto/Window/EventNode.hpp>
#include <Cacto/UI/InflatableNode.hpp>

namespace cacto
{

    class CACTO_UI_API UIRoot
        : public virtual RootNode,
          public virtual DrawNode,
          public virtual EventNode,
          public virtual InflatableNode
    {

    public:
        szt getChildCount() const override;
        Node *const getChild(szt index = 0) const override;

        Node *getFocusedNode() const;

        void append(Node &child);
        void remove(Node &child);

        UIRoot();
        virtual ~UIRoot();

        UIRoot(const UIRoot &other);
        UIRoot &operator=(const UIRoot &other);

    protected:
        void onAppend(Node &child) override;
        void onRemove(Node &child) override;

        bool onBubble(Node &target, const sf::Event &event) override;

    private:
        Node *m_child;
        Node *m_focusedNode;
    };

}

#endif