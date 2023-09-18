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

    bool Node::handleSignal(Node *const target, const Signal &signal)
    {
        return false;
    }

    bool Node::dispatchSignal(Node *const target, const Signal &signal)
    {
        auto handled = false;
        auto childCount = getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = getChild(i);
            handled |= child && child->dispatchSignal(target, signal);
        }
        return handled;
    }

    bool Node::bubbleSignal(Node *const target, const Signal &signal)
    {
        auto handled = false;
        auto *parent = getParent();
        handled |= parent && parent->bubbleSignal(target, signal);
        return handled;
    }

}