#include <stdexcept>
#include <Cacto/Core/LeafNode.hpp>

namespace cacto
{

    szt LeafNode::getChildCount() const
    {
        return 0;
    }

    SharedNode LeafNode::getChild(szt index) const
    {
        return nullptr;
    }

    LeafNode::LeafNode() = default;

    LeafNode::~LeafNode() = default;

    void LeafNode::onAppend(const SharedNode &child)
    {
        throw std::runtime_error("Leaf nodes can not hold childs");
    }

    void LeafNode::onRemove(const SharedNode &child)
    {
        throw std::runtime_error("Leaf nodes can not hold childs");
    }

}