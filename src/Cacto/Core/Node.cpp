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

    void Node::append(const SharedNode &child)
    {
        child->onAttach(*this);
    }

    void Node::remove(const SharedNode &child)
    {
        child->onDetach(*this);
    }

    Node::Node() = default;

    Node::~Node() = default;

    void Node::onAttach(Node &parent)
    {
        if (getParent())
            throw std::runtime_error("The node is already attached to another parent");
        auto current = &parent;
        while (current)
        {
            if (current == this)
                throw std::runtime_error("The node its own ancestor");
            current = current->getParent();
        }
    }

    void Node::onDetach(Node &parent)
    {
        if (getParent() != &parent)
            throw std::runtime_error("The node is already attached to another parent");
    }

}