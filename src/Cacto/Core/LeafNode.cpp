#include <stdexcept>
#include <Cacto/Core/LeafNode.hpp>

namespace cacto
{

    szt LeafNode::getChildCount() const
    {
        return 0;
    }

    Shared<Node> LeafNode::getChild(szt index) const
    {
        return nullptr;
    }

    void LeafNode::onAppend(const Shared<Node> &child)
    {
        throw std::runtime_error("Leaf nodes can not hold children");
    }

    void LeafNode::onRemove(const Shared<Node> &child)
    {
        throw std::runtime_error("Leaf nodes can not hold children");
    }

}