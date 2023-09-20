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

    void GenericNode::attach(Node *const parent)
    {
        Node::attach(parent);
        m_parent = parent;
    }

    void GenericNode::detach(Node *const parent)
    {
        Node::detach(parent);
        m_parent = nullptr;
    }

    void GenericNode::append(const SharedNode &child)
    {
        Node::append(child);
        child->attach(this);
        m_children.push_back(child);
    }

    void GenericNode::remove(const SharedNode &child)
    {
        Node::remove(child);
        child->detach(this);
        std::remove(m_children.begin(), m_children.end(), child);
    }

    bool GenericNode::dispatchSignal(const cacto::Signal &signal)
    {
        auto handled = UpdateNode::handleSignal(nullptr, signal) || DrawNode::handleSignal(nullptr, signal) || Node::dispatchSignal(signal) || EventNode::handleSignal(nullptr, signal);
        return handled;
    }

    bool GenericNode::bubbleSignal(Node& target, const cacto::Signal &signal)
    {
        auto handled = UpdateNode::handleSignal(&target, signal) || DrawNode::handleSignal(&target, signal) || EventNode::handleSignal(&target, signal) || Node::bubbleSignal(target, signal);
        return handled;
    }

    GenericNode::GenericNode()
        : m_parent(nullptr), m_children()
    {
    }

    GenericNode::~GenericNode() = default;

}