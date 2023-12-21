#include <stdexcept>
#include <Cacto/Core/RootNode.hpp>

namespace cacto
{

    Node*const RootNode::getParent() const
    {
        return nullptr;
    }

    void RootNode::onAttach(Node &parent)
    {
        throw std::runtime_error("Root nodes can not be holded");
    }

    void RootNode::onDetach(Node &parent)
    {
        throw std::runtime_error("Root nodes can not be holded");
    }

}