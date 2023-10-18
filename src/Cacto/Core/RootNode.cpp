#include <stdexcept>
#include <Cacto/Core/RootNode.hpp>

namespace cacto
{

    Node *const RootNode::getParent() const
    {
        return nullptr;
    }

    RootNode::RootNode() = default;

    RootNode::~RootNode() = default;

    void RootNode::onAttach(Node& parent)
    {
        throw std::runtime_error("Root nodes can not be holded");
    }

    void RootNode::onDetach(Node& parent)
    {
        throw std::runtime_error("Root nodes can not be holded");
    }

}