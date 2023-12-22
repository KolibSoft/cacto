#include <stdexcept>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Core/Node.hpp>

namespace cacto
{

    const std::string &Node::getId() const
    {
        return NoId;
    }

    i32t Node::getChildIndex(const Node &child) const
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

    const std::string Node::NoId;

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

    szt getXmlNodeStackSize()
    {
        return node::XmlConverter::getStackSize();
    }

    std::vector<std::shared_ptr<Node>> takeXmlNodeStack(szt index)
    {
        auto stack = node::XmlConverter::takeStackFrame(index);
        return std::move(stack);
    }

    namespace node
    {

        szt XmlConverter::getStackSize()
        {
            return s_Stack.size();
        }

        std::vector<std::shared_ptr<Node>> XmlConverter::takeStackFrame(szt index)
        {
            std::vector<std::shared_ptr<Node>> frame{s_Stack.begin() + index, s_Stack.end()};
            return std::move(frame);
        }

        void XmlConverter::pushStack(const std::shared_ptr<Node> &node)
        {
            s_Stack.push_back(node);
        }

        std::vector<std::shared_ptr<Node>> XmlConverter::s_Stack{};

    }

}