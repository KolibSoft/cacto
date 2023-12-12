#include <stdexcept>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Core/Node.hpp>

namespace cacto
{

    i32t Node::getChildIndex(const Node &child) const
    {
        for (szt i = 0; i < getChildCount(); i++)
        {
            auto _child = getChild(i);
            if (_child == &child)
                return i;
        }
        return -1;
    }

    void Node::link(Node &parent, Node &child)
    {
        if (child.getParent() != nullptr)
            throw std::runtime_error("The child was linked to another parent");
        auto current = &parent;
        while (current)
        {
            if (current == &child)
                throw std::runtime_error("The child is its own ancestor");
            current = current->getParent();
        }
        parent.onAppend(child);
        child.onAttach(parent);
    }

    void Node::unlink(Node &parent, Node &child)
    {
        if (child.getParent() != &parent)
            throw std::runtime_error("The child was linked to another parent");
        child.onDetach(parent);
        parent.onRemove(child);
    }

    XmlValue toXml(const Node *const &node)
    {
        auto xml = XmlConverter<Node>::xml(node);
        return std::move(xml);
    }

    void fromXml(Node *&node, const XmlValue &xml)
    {
        auto _node = XmlConverter<Node>::value(xml);
        node = _node;
    }

}