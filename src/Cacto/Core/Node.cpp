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

    Node::Node() = default;

    Node::~Node()
    {
        auto childCount = getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = getChild(i);
            onRemove(child);
        }
    }

    void Node::onAppend(const SharedNode &child)
    {
        child->onAttach(*this);
    }

    void Node::onRemove(const SharedNode &child)
    {
        child->onDetach(*this);
    }

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