#include <stdexcept>
#include <SFML/Graphics/RenderStates.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Graphics/Skeleton.hpp>

namespace cacto
{

    namespace skeleton
    {

        const sf::Vector2f &Options::getCoords() const
        {
            return m_coords;
        }

        Options &Options::setCoords(const sf::Vector2f &value)
        {
            m_coords = value;
            return *this;
        }

        Relation Options::getRelation() const
        {
            return m_relation;
        }

        Options &Options::setRelation(Relation value)
        {
            m_relation = value;
            return *this;
        }

        Options::Options(const sf::Vector2f &coords, Relation relation)
            : m_coords(coords),
              m_relation(relation)
        {
        }

        Options::~Options() = default;

    }

    const std::string &Skeleton::getId() const
    {
        return m_id;
    }

    Skeleton &Skeleton::setId(const std::string &value)
    {
        m_id = value;
        return *this;
    }

    const sf::Transformable &Skeleton::asTransformable() const
    {
        return m_transformable;
    }

    sf::Transformable &Skeleton::asTransformable()
    {
        return m_transformable;
    }

    ParentNode *const Skeleton::getParent() const
    {
        return m_parent;
    }

    szt Skeleton::getChildCount() const
    {
        return m_holders.size();
    }

    ChildNode *const Skeleton::getChild(szt index) const
    {
        if (index >= m_holders.size())
            return nullptr;
        auto &holder = m_holders.at(index);
        return holder.child;
    }

    const Skeleton::Options *const Skeleton::getOptions(const Node &child) const
    {
        for (auto &holder : m_holders)
            if (holder.child == &child)
                return &holder.options;
        return nullptr;
    }

    Skeleton::Options *const Skeleton::getOptions(const Node &child)
    {
        for (auto &holder : m_holders)
            if (holder.child == &child)
                return &holder.options;
        return nullptr;
    }

    void Skeleton::attach(ParentNode &parent)
    {
        if (m_parent == &parent)
            return;
        if (m_parent != nullptr)
            throw std::runtime_error("This node is already attached to another parent");
        if (parent.hasAncestor(*this))
            throw std::runtime_error("This node is an ancestor");
        m_parent = &parent;
        parent.append(*this);
    }

    void Skeleton::detach()
    {
        if (m_parent == nullptr)
            return;
        m_parent->remove(*this);
        m_parent = nullptr;
    }

    void Skeleton::append(ChildNode &child)
    {
        if (getChildIndex(child) >= 0)
            return;
        if (child.getParent() != nullptr && child.getParent() != this)
            throw std::runtime_error("The node is already attached to another parent");
        if (hasAncestor(child))
            throw std::runtime_error("The node is an ancestor");
        holder holder{};
        holder.child = &child;
        holder.options = {};
        m_holders.push_back(holder);
        child.attach(*this);
    }

    Skeleton &Skeleton::append(ChildNode &child, const Options &options)
    {
        append(child);
        m_holders.back().options = options;
        return *this;
    }

    void Skeleton::remove(ChildNode &child)
    {
        auto index = getChildIndex(child);
        if (getChildIndex(child) >= 0)
        {
            m_holders.erase(m_holders.begin() + index);
            child.detach();
        }
    }

    void Skeleton::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (m_holders.size() > 0)
        {
            for (auto &holder : m_holders)
            {
                switch (holder.options.getRelation())
                {
                case Relation::Body:
                {
                    auto _states = states;
                    _states.transform *= m_transformable.getTransform();
                    _states.transform.translate(holder.options.getCoords());
                    DrawNode::draw(*holder.child, target, _states);
                }
                break;
                case Relation::Bone:
                {
                    auto _states = states;
                    _states.transform.translate(m_transformable.getTransform().transformPoint(holder.options.getCoords()));
                    DrawNode::draw(*holder.child, target, _states);
                }
                break;
                default:
                    break;
                }
            }
        }
    }

    Skeleton::Skeleton()
        : m_id(),
          m_transformable(),
          m_parent(),
          m_holders()
    {
    }

    Skeleton::~Skeleton()
    {
        detach();
        clearChildren();
    }

    std::string toString(Skeleton::Relation relation)
    {
        if (relation == Skeleton::Relation::Body)
            return "Body";
        else if (relation == Skeleton::Relation::Bone)
            return "Bone";
        else
            throw std::runtime_error("Unsupported relation");
    }

    void fromString(Skeleton::Relation &relation, const std::string &string)
    {
        if (string == "Body")
            relation = Skeleton::Relation::Body;
        else if (string == "Bone")
            relation = Skeleton::Relation::Bone;
        else
            throw std::runtime_error("Unsupported relation");
    }

    XmlValue toXml(const Skeleton &skeleton)
    {
        XmlValue xml = toXml(skeleton.asTransformable());
        xml.setName("Skeleton");
        xml["id"] = skeleton.getId();
        auto &content = xml.asContent();
        for (szt i = 0; i < skeleton.getChildCount(); i++)
        {
            auto child = skeleton.getChild(i);
            if (child)
            {
                auto options = skeleton.getOptions(*child);
                auto child_xml = cacto::toXml(child);
                child_xml["options:coords"] = cacto::toString(options->getCoords());
                child_xml["options:relation"] = cacto::toString(options->getRelation());
                content.push_back(std::move(child_xml));
            }
        }
        return std::move(xml);
    }

    void fromXml(Skeleton &skeleton, const XmlValue &xml)
    {
        fromXml(skeleton.asTransformable(), xml);
        skeleton.setId(xml.getAttribute("id"));
        if (xml.isTag())
            for (auto &item : xml.asContent())
            {
                Node *node = nullptr;
                cacto::fromXml(node, item);
                auto child = dynamic_cast<ChildNode *>(node);
                if (child)
                {
                    sf::Vector2f coords{};
                    cacto::fromString(coords, item.getAttribute("options:coords", "0,0"));
                    Skeleton::Relation relation{};
                    cacto::fromString(relation, item.getAttribute("options:relation", "Body"));
                    skeleton
                        .append(*child,
                                Skeleton::Options()
                                    .setCoords(coords)
                                    .setRelation(relation));
                }
            }
    }

    namespace skeleton
    {

        XmlValue XmlConverter::toXml(const Node *const value) const
        {
            const Skeleton *skeleton = nullptr;
            if (value && typeid(*value) == typeid(Skeleton) && (skeleton = dynamic_cast<const Skeleton *>(value)))
            {
                auto xml = cacto::toXml(*skeleton);
                return std::move(xml);
            }
            return nullptr;
        }

        Node *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.getKind() == XmlValue::Tag && xml.getName() == "Skeleton")
            {
                auto skeleton = std::make_shared<Skeleton>();
                cacto::fromXml(*skeleton, xml);
                Node::XmlStack.push(skeleton);
                return skeleton.get();
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }
}