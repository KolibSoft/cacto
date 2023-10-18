#include <stdexcept>
#include <algorithm>
#include <Cacto/Game/GameNode.hpp>

namespace cacto
{

    Node *const GameNode::getParent() const
    {
        return m_parent;
    }

    szt GameNode::getChildCount() const
    {
        auto count = m_children.size();
        return count;
    }

    Node *const GameNode::getChild(szt index) const
    {
        if (index < m_children.size())
        {
            auto child = m_children[index];
            return child;
        }
        return nullptr;
    }

    void GameNode::append(Node &child)
    {
        Node::link(*this, child);
    }

    void GameNode::remove(Node &child)
    {
        Node::unlink(*this, child);
    }

    GameNode::GameNode()
        : m_parent(), m_children()
    {
    }

    GameNode::~GameNode() = default;

    void GameNode::onAppend(Node &child)
    {
        m_children.push_back(&child);
    }

    void GameNode::onRemove(Node &child)
    {
        std::remove(m_children.begin(), m_children.end(), &child);
    }

    void GameNode::onAttach(Node &parent)
    {
        m_parent = &parent;
    }

    void GameNode::onDetach(Node &parent)
    {
        m_parent = nullptr;
    }

}