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
        if (xml.isTag())
            xml["bag:tag"] = node::XmlConverter::Bag.getTag(*const_cast<Node *>(node));
        return std::move(xml);
    }

    void fromXml(Node *&node, const XmlValue &xml)
    {
        auto _node = XmlConverter<Node>::value(xml);
        if (_node)
            node::XmlConverter::Bag.set(*_node, xml.getAttribute("bag:tag"));
        node = _node;
    }

    namespace node
    {

        const std::string &Bag::getTag(const Node &node) const
        {
            for (auto &pair : m_map)
                if (pair.first == &node)
                    return pair.second;
            return NoTag;
        }

        Node *const Bag::getNode(const std::string &tag) const
        {
            for (auto &pair : m_map)
                if (pair.second == tag)
                    return pair.first;
            return nullptr;
        }

        void Bag::set(Node &node, const std::string &tag)
        {
            m_map[&node] = tag;
        }

        szt Bag::getCount() const
        {
            return m_map.size();
        }

        Bag::Bag()
            : m_map()
        {
        }

        Bag::~Bag()
        {
            for (auto &pair : m_map)
                if (pair.first)
                    delete pair.first;
        }

        Bag::Bag(Bag &&other)
            : m_map(std::move(other.m_map))
        {
        }

        Bag &Bag::operator=(Bag &&other)
        {
            m_map = std::move(other.m_map);
            return *this;
        }

        const std::string Bag::NoTag{""};

        Bag XmlConverter::Bag{};

    }

}