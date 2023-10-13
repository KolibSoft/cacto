#include <stdexcept>
#include <algorithm>
#include <Cacto/Common/GenericNode.hpp>

namespace cacto
{

    SharedNode GenericNode::getParent() const
    {
        auto parent = m_parent.lock();
        return parent;
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
        auto self = as<Node>();
        Node::link(self, child);
    }

    void GenericNode::remove(const SharedNode &child)
    {
        auto self = as<Node>();
        Node::unlink(self, child);
    }

    void GenericNode::attach(const SharedNode &parent)
    {
        auto self = as<Node>();
        Node::link(parent, self);
    }

    void GenericNode::detach(const SharedNode &parent)
    {
        auto self = as<Node>();
        Node::unlink(parent, self);
    }

    GenericNode::GenericNode()
        : m_parent(), m_children()
    {
    }

    GenericNode::~GenericNode() = default;

    void GenericNode::onAppend(const SharedNode &child)
    {
        m_children.push_back(child);
    }

    void GenericNode::onRemove(const SharedNode &child)
    {
        std::remove(m_children.begin(), m_children.end(), child);
    }

    void GenericNode::onAttach(const SharedNode &parent)
    {
        if (getParent() != nullptr)
            throw std::runtime_error("Node attached to another parent");
        m_parent = parent;
    }

    void GenericNode::onDetach(const SharedNode &parent)
    {
        if (getParent() != parent)
            throw std::runtime_error("Node attached to another parent");
        m_parent.reset();
    }

}