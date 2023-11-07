#include <stdexcept>
#include <Cacto/Core/LeafNode.hpp>

namespace cacto
{

    szt LeafNode::getChildCount() const
    {
        return 0;
    }

    Node *const LeafNode::getChild(szt index) const
    {
        return nullptr;
    }

    void LeafNode::onAppend(Node &child)
    {
        throw std::runtime_error("Leaf nodes can not hold children");
    }

    void LeafNode::onRemove(Node &child)
    {
        throw std::runtime_error("Leaf nodes can not hold children");
    }

}