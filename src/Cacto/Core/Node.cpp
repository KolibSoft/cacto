#include <stdexcept>
#include <Cacto/Core/Node.hpp>

namespace cacto
{

    void Node::link(const SharedNode &parent, const SharedNode &child)
    {
        auto current = parent;
        while (current)
        {
            if (current == child)
                throw std::runtime_error("The node is its own ancestor");
            current = current->getParent();
        }
        parent->onAppend(child);
        child->onAttach(parent);
    }

    void Node::unlink(const SharedNode &parent, const SharedNode &child)
    {
        child->onDetach(parent);
        parent->onRemove(child);
    }

}