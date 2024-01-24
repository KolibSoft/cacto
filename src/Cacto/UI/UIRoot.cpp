#include <SFML/Window/Event.hpp>
#include <Cacto/Window/Focusable.hpp>
#include <Cacto/UI/UIRoot.hpp>

namespace cacto
{

    szt UIRoot::getChildCount() const
    {
        return m_child ? 1 : 0;
    }

    Node *const UIRoot::getChild(szt index) const
    {
        return index == 0 ? m_child : nullptr;
    }

    Node *UIRoot::getFocusedNode() const
    {
        return m_focusedNode;
    }

    void UIRoot::append(Node &child)
    {
        Node::link(*this, child);
    }

    void UIRoot::remove(Node &child)
    {
        Node::unlink(*this, child);
    }

    UIRoot::UIRoot()
        : m_child(nullptr),
          m_focusedNode(nullptr)
    {
    }

    UIRoot::~UIRoot()
    {
        Node::unlink(*this, *m_child);
    }

    UIRoot::UIRoot(const UIRoot &other)
        : m_child(nullptr),
          m_focusedNode(nullptr)
    {
    }

    UIRoot &UIRoot::operator=(const UIRoot &other)
    {
        return *this;
    }

    void UIRoot::onAppend(Node &child)
    {
        if (m_child != nullptr)
            throw std::runtime_error("This node has already another child");
        m_child = &child;
    }

    void UIRoot::onRemove(Node &child)
    {
        if (m_child != &child)
            throw std::runtime_error("This node has already another child");
        m_child = nullptr;
    }

    bool UIRoot::onBubble(Node &target, const sf::Event &event)
    {
        if (event.type == sf::Event::GainedFocus)
        {
            if (m_focusedNode && m_focusedNode != &target)
            {
                auto focusable = dynamic_cast<cacto::Focusable *>(m_focusedNode);
                focusable->unfocus();
            }
            m_focusedNode = &target;
        }
        auto handled = bubbleParent(target, event);
        return handled;
    }

}