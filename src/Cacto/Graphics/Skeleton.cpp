#include <stdexcept>
#include <Cacto/Core/Utils.hpp>
#include <Cacto/Graphics/Skeleton.hpp>

namespace cacto
{

    Node *const Skeleton::getParent() const
    {
        return m_parent;
    }

    szt Skeleton::getChildCount() const
    {
        return m_holders.size();
    }

    Node *const Skeleton::getChild(szt index) const
    {
        if (m_holders.size() <= index)
            return nullptr;
        auto &holder = m_holders.at(index);
        return &holder.getNode();
    }

    const Skeleton::Holder *const Skeleton::getHolder(const Node &child) const
    {
        for (auto &holder : m_holders)
            if (&holder.getNode() == &child)
                return &holder;
        return nullptr;
    }

    Skeleton::Holder *const Skeleton::getHolder(const Node &child)
    {
        for (auto &holder : m_holders)
            if (&holder.getNode() == &child)
                return &holder;
        return nullptr;
    }

    Skeleton::Holder &Skeleton::append(Node &child, bool internal)
    {
        Node::link(*this, child);
        auto &holder = m_holders.back();
        holder.setInternal();
        return holder;
    }

    void Skeleton::remove(Node &child)
    {
        Node::unlink(*this, child);
    }

    Skeleton::Skeleton()
        : m_parent(nullptr),
          m_holders()
    {
    }

    Skeleton::~Skeleton()
    {
        while (m_holders.size() > 0)
            Node::unlink(*this, m_holders.back().getNode());
    }

    Skeleton::Skeleton(const Skeleton &other)
        : Transformable(other),
          m_parent(nullptr)
    {
    }

    Skeleton &Skeleton::operator=(const Skeleton &other)
    {
        sf::Transformable::operator=(other);
        return *this;
    }

    Skeleton::Skeleton(Skeleton &&other)
        : Transformable(std::move(other)),
          m_parent(nullptr)
    {
    }

    Skeleton &Skeleton::operator=(Skeleton &&other)
    {
        sf::Transformable::operator=(std::move(other));
        return *this;
    }

    void Skeleton::onAttach(Node &parent)
    {
        m_parent = &parent;
    }

    void Skeleton::onDetach(Node &parent)
    {
        m_parent = nullptr;
    }

    void Skeleton::onAppend(Node &child)
    {
        Holder holder{child, false};
        m_holders.push_back(holder);
    }

    void Skeleton::onRemove(Node &child)
    {
        auto index = getChildIndex(child);
        m_holders.erase(m_holders.begin() + index);
    }

    void Skeleton::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (m_holders.size() > 0)
        {
            for (auto &holder : m_holders)
            {
                switch (holder.getRelation())
                {
                case Skeleton::Body:
                {
                    auto _states = states;
                    _states.transform *= getTransform();
                    _states.transform.translate(holder.getCoord());
                    DrawNode::draw(holder.getNode(), target, _states);
                }
                break;
                case Skeleton::Bone:
                {
                    auto _states = states;
                    _states.transform.translate(getTransform().transformPoint(holder.getCoord()));
                    DrawNode::draw(holder.getNode(), target, _states);
                }
                break;
                default:
                    break;
                }
            }
        }
    }

    std::string toString(Skeleton::Relation relation)
    {
        if (relation == Skeleton::Body)
            return "Body";
        else if (relation == Skeleton::Bone)
            return "Bone";
        else
            throw std::runtime_error("Unsupported relation");
    }

    void fromString(Skeleton::Relation relation, const std::string &string)
    {
        if (string == "Body")
            relation = Skeleton::Body;
        else if (string == "Bone")
            relation = Skeleton::Bone;
        else
            throw std::runtime_error("Unsupported relation");
    }

    XmlValue toXml(const Skeleton &skeleton)
    {
        XmlValue xml{"Skeleton", {}};
        auto &content = xml.asContent();
        for (szt i = 0; i < skeleton.getChildCount(); i++)
        {
            auto child = skeleton.getChild(i);
            auto holder = skeleton.getHolder(*child);
            auto _xml = cacto::toXml(child);
            _xml["holder:coord"] = cacto::toString(holder->getCoord());
            _xml["holder:relation"] = cacto::toString(holder->getRelation());
            content.push_back(xml);
        }
        return xml;
    }

    void fromXml(Skeleton &skeleton, const XmlValue &xml)
    {
        skeleton = {};
        if (xml.isTag())
            for (auto &item : xml.asContent())
            {
                Node *node = nullptr;
                cacto::fromXml(node, item);
                sf::Vector2f coord{};
                cacto::fromString(coord, item.getAttribute("holder:coord", "0,0"));
                Skeleton::Relation relation{};
                cacto::fromString(relation, item.getAttribute("holder:relation", "Body"));
                skeleton
                    .append(*node, true)
                    .setCoord(coord)
                    .setRelation(relation);
            }
    }

    namespace skeleton
    {

        const sf::Vector2f &Holder::getCoord() const
        {
            return m_coord;
        }

        Holder &Holder::setCoord(const sf::Vector2f &value)
        {
            m_coord = value;
            return *this;
        }

        Skeleton::Relation Holder::getRelation() const
        {
            return m_relation;
        }

        Holder &Holder::setRelation(Skeleton::Relation value)
        {
            m_relation = value;
            return *this;
        }

        Holder::Holder(Node &node, bool internal)
            : node::Holder(node, internal),
              m_coord(),
              m_relation(Skeleton::Body)
        {
        }

        Holder::~Holder() = default;

        XmlValue XmlConverter::toXml(const Node *const value) const
        {
            const Skeleton *skeleton = nullptr;
            if (value && (skeleton = dynamic_cast<const Skeleton *>(value)))
            {
                auto xml = cacto::toXml(*skeleton);
                return xml;
            }
            return nullptr;
        }

        Node *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.getKind() == XmlValue::Tag && xml.getName() == "Skeleton")
            {
                auto skeleton = new Skeleton();
                cacto::fromXml(*skeleton, xml);
                return skeleton;
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}