#include <stdexcept>
#include <Cacto/Core/RootNode.hpp>

namespace cacto
{

    SharedNode RootNode::getParent() const
    {
        return nullptr;
    }

    RootNode::RootNode() = default;

    RootNode::~RootNode() = default;

    void RootNode::onAttach(const SharedNode &child)
    {
        throw std::runtime_error("Root nodes can not be holded");
    }

    void RootNode::onDetach(const SharedNode &child)
    {
        throw std::runtime_error("Root nodes can not be holded");
    }

}