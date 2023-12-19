#include <stdexcept>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Core/Node.hpp>

namespace cacto
{

    const std::string &Node::getId() const
    {
        return NoId;
    }

    i32t Node::getChildIndex(const Shared<const Node> &child) const
    {
        if (child == nullptr)
            return -1;
        for (szt i = 0; i < getChildCount(); i++)
        {
            auto _child = getChild(i);
            if (_child == child)
                return i;
        }
        return -1;
    }

    void Node::link(const Shared<Node> &parent, const Shared<Node> &child)
    {
        if (parent == nullptr)
            throw std::runtime_error("The parent was null");

        if (child == nullptr)
            throw std::runtime_error("The child was null");

        if (child->getParent() != nullptr)
            throw std::runtime_error("The child was linked to another parent");

        auto current = parent;
        while (current)
        {
            if (current == child)
                throw std::runtime_error("The child is its own ancestor");
            current = current->getParent();
        }
        parent->onAppend(child);
        child->onAttach(parent);
    }

    void Node::unlink(const Shared<Node> &parent, const Shared<Node> &child)
    {
        if (parent == nullptr)
            throw std::runtime_error("The parent was null");

        if (child == nullptr)
            throw std::runtime_error("The child was null");

        if (child->getParent() != parent)
            throw std::runtime_error("The child was linked to another parent");

        child->onDetach(parent);
        parent->onRemove(child);
    }

    const std::string Node::NoId;

    XmlValue toXml(const Shared<const Node> &node)
    {
        auto xml = XmlConverter<Node>::xml(node);
        return std::move(xml);
    }

    void fromXml(Shared<Node> &node, const XmlValue &xml)
    {
        auto _node = XmlConverter<Node>::value(xml);
        node = _node;
    }

}