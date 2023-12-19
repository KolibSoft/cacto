#include <stdexcept>
#include <Cacto/Core/RootNode.hpp>

namespace cacto
{

    Shared<Node> RootNode::getParent() const
    {
        return nullptr;
    }

    void RootNode::onAttach(const Shared<Node> &parent)
    {
        throw std::runtime_error("Root nodes can not be holded");
    }

    void RootNode::onDetach(const Shared<Node> &parent)
    {
        throw std::runtime_error("Root nodes can not be holded");
    }

}