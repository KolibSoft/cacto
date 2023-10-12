#include <Cacto/Core/Node.hpp>

namespace cacto
{

    void Node::link(const SharedNode &parent, const SharedNode &child)
    {
        parent->onAppend(child);
        child->onAttach(parent);
    }

    void Node::unlink(const SharedNode &parent, const SharedNode &child)
    {
        child->onDetach(parent);
        parent->onRemove(child);
    }

}