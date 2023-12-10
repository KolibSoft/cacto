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

    void Node::clearChildren()
    {
        Node *node = nullptr;
        while ((node = getChild()))
            Node::unlink(*this, *node);
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
        if (node == nullptr)
            return nullptr;
        for (auto &converter : XmlConverter<Node>::Converters)
        {
            auto json = converter->toXml(node);
            if (json != nullptr)
                return json;
        }
        return nullptr;
    }

    void fromXml(Node *&node, const XmlValue &xml)
    {
        if (xml == nullptr)
            node = nullptr;
        for (auto &converter : XmlConverter<Node>::Converters)
        {
            node = converter->fromXml(xml);
            if (node)
                return;
        }
    }

    namespace node
    {

        Node &Holder::getNode() const
        {
            return *m_node;
        }

        bool Holder::isInternal() const
        {
            return m_internal;
        }

        void Holder::setInternal(bool value)
        {
            m_internal = value;
        }

        Holder::Holder(Node &node, bool internal)
            : m_node(&node),
              m_internal(internal)
        {
        }

        Holder::~Holder()
        {
            if (m_internal)
            {
                delete m_node;
                m_node = nullptr;
            }
        }

    }

}