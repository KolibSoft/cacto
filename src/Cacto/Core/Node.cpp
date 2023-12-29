#include <stdexcept>
#include <Cacto/Core/Node.hpp>

namespace cacto
{

    i32t Node::getChildIndex(const ChildNode &child) const
    {
        auto childCount = getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto _child = getChild(i);
            if (_child == &child)
                return i;
        }
        return -1;
    }

    bool Node::hasDescendant(const Node &node) const
    {
        if (&node == this)
            return true;
        auto childCount = getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = getChild(i);
            if (child && child->hasDescendant(node))
                return true;
        }
        return false;
    }

    bool Node::hasAncestor(const Node &node) const
    {
        if (&node == this)
            return true;
        auto parent = getParent();
        if (parent && parent->hasAncestor(node))
            return true;
        return false;
    }

    ResourceStack<Node> Node::XmlStack{};

    XmlValue toXml(const Node *const &node)
    {
        auto xml = XmlConverter<Node>::xml(node);
        return std::move(xml);
    }

    void fromXml(Node *&node, const XmlValue &xml)
    {
        auto value = XmlConverter<Node>::value(xml);
        node = value;
    }

}