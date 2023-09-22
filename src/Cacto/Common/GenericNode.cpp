#include <algorithm>
#include <Cacto/Common/GenericNode.hpp>

namespace cacto
{

    Node *const GenericNode::getParent() const
    {
        return m_parent;
    }

    szt GenericNode::getChildCount() const
    {
        auto count = m_children.size();
        return count;
    }

    SharedNode GenericNode::getChild(szt index) const
    {
        if (index < m_children.size())
        {
            auto child = m_children[index];
            return child;
        }
        return nullptr;
    }

    void GenericNode::append(const SharedNode &child)
    {
        onAppend(child);
    }

    void GenericNode::remove(const SharedNode &child)
    {
        onRemove(child);
    }

    GenericNode::GenericNode()
        : m_parent(nullptr), m_children()
    {
    }

    GenericNode::~GenericNode() = default;

    void GenericNode::onAppend(const SharedNode &child)
    {
        Node::onAppend(child);
        m_children.push_back(child);
    }

    void GenericNode::onRemove(const SharedNode &child)
    {
        Node::onRemove(child);
        std::remove(m_children.begin(), m_children.end(), child);
    }

    void GenericNode::onAttach(Node &parent)
    {
        Node::onAttach(parent);
        m_parent = &parent;
    }

    void GenericNode::onDetach(Node &parent)
    {
        Node::onDetach(parent);
        m_parent = nullptr;
    }

}