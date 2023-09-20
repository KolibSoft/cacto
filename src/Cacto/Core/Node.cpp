#include <stdexcept>
#include <Cacto/Core/Node.hpp>

namespace cacto
{

    Node *const Node::getParent() const
    {
        return nullptr;
    }

    szt Node::getChildCount() const
    {
        return 0;
    }

    SharedNode Node::getChild(szt index) const
    {
        return nullptr;
    }

    void Node::attach(Node *const parent)
    {
        if (getParent())
            throw std::runtime_error("The node is already attached to another parent");
    }

    void Node::detach(Node *const parent)
    {
        if (getParent() != parent)
            throw std::runtime_error("The node is already attached to another parent");
    }

    void Node::append(const SharedNode &child)
    {
        if (child->getParent())
            throw std::runtime_error("The node is already attached to another parent");
    }

    void Node::remove(const SharedNode &child)
    {
        if (child->getParent() != this)
            throw std::runtime_error("The node is already attached to another parent");
    }

    Node::Node() = default;

    Node::~Node() = default;

}