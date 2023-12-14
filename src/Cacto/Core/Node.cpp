#include <stdexcept>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Core/Node.hpp>

namespace cacto
{

    const std::string &Node::getTag() const
    {
        return NoTag;
    }

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

    Node *const Node::firstAncestor(const NodePredicate &predicate) const
    {
        if (predicate(*this))
            return const_cast<Node *const>(this);
        auto parent = getParent();
        if (parent)
        {
            auto node = parent->firstAncestor(predicate);
            return node;
        }
        return nullptr;
    }

    Node *const Node::firstDescendant(const NodePredicate &predicate) const
    {
        if (predicate(*this))
            return const_cast<Node *const>(this);
        for (szt i = 0; i < getChildCount(); i++)
        {
            auto child = getChild(i);
            auto node = child->firstDescendant(predicate);
            if (node)
                return node;
        }
        return nullptr;
    }

    const std::string Node::NoTag{};

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