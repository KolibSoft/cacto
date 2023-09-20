#include <stdexcept>
#include <Cacto/Core/LeafNode.hpp>

namespace cacto
{

    void LeafNode::append(const SharedNode &child)
    {
        throw std::runtime_error("Leaf nodes can not hold childs");
    }

    void LeafNode::remove(const SharedNode &child)
    {
        throw std::runtime_error("Leaf nodes can not hold childs");
    }

    LeafNode::LeafNode() = default;

    LeafNode::~LeafNode() = default;

}