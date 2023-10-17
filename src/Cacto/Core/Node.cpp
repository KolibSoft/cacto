#include <stdexcept>
#include <Cacto/Core/Node.hpp>

namespace cacto
{

    void Node::link(Node &parent, const SharedNode &child)
    {
        if (!child)
            throw std::runtime_error("The child was nullptr");
        if (child->getParent() != nullptr)
            throw std::runtime_error("The child was linked to another parent");
        auto current = &parent;
        while (current)
        {
            if (current == child.get())
                throw std::runtime_error("The child is its own ancestor");
            current = current->getParent();
        }
        parent.onAppend(child);
        child->onAttach(parent);
    }

    void Node::unlink(Node &parent, const SharedNode &child)
    {
        if (!child)
            throw std::runtime_error("The child was nullptr");
        if (child->getParent() != &parent)
            throw std::runtime_error("The child was linked to another parent");
        child->onDetach(parent);
        parent.onRemove(child);
    }

}