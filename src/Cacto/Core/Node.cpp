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

    bool Node::handleSignal(const Signal &signal)
    {
        return false;
    }

    bool Node::dispatchSignal(const Signal &signal)
    {
        auto handled = false;
        auto childCount = getChildCount();
        for (auto i = 0; i < childCount; i++)
        {
            auto child = getChild(i);
            if (handled = (child && child->dispatchSignal(signal)))
                break;
        }
        handled = handled || handleSignal(signal);
        return handled;
    }

    bool Node::bubbleSignal(const Signal &signal)
    {
        auto handled = false;
        auto *current = this;
        while (current && !(handled = current->handleSignal(signal)))
            current = current->getParent();
        return handled;
    }

    bool Node::spreadSignal(const Signal &signal)
    {
        auto handled = false;
        auto *root = this;
        while (root->getParent())
            root = root->getParent();
        handled = root->dispatchSignal(signal);
        return handled;
    }

}