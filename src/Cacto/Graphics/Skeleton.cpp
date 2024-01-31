#include <stdexcept>
#include <SFML/Graphics/RenderStates.hpp>
#include <Cacto/Core/VectorUtils.hpp>
#include <Cacto/Graphics/NodeUtils.hpp>
#include <Cacto/Graphics/VectorUtils.hpp>
#include <Cacto/Graphics/TransformableUtils.hpp>
#include <Cacto/Graphics/Skeleton.hpp>

namespace cacto
{

    const sf::Transformable &Skeleton::asTransformable() const
    {
        return m_transformable;
    }

    sf::Transformable &Skeleton::asTransformable()
    {
        return m_transformable;
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

    void Skeleton::remove(ChildNode &child)
    {
        auto index = getChildIndex(child);
        if (getChildIndex(child) >= 0)
        {
            m_holders.erase(m_holders.begin() + index);
            child.detach();
            for (auto it = m_bag.begin(); it != m_bag.end(); ++it)
                if (it->get() == &child)
                {
                    m_bag.erase(it);
                    break;
                }
        }
    }

    Skeleton &Skeleton::append(ChildNode &child, const Options &options)
    {
        append(child);
        auto _options = getOptions(child);
        if (_options)
            *_options = options;
        return *this;
    }

    Skeleton &Skeleton::append(const std::shared_ptr<ChildNode> &child, const Options &options)
    {
        append(*child, options);
        m_bag.push_back(child);
        return *this;
    }

    XmlValue Skeleton::toXml() const
    {
        XmlValue xml{"Skeleton", {}};
        xml["id"] = getId();
        auto txml = cacto::toXml(m_transformable);
        for (auto &pair : txml.asAttributes())
            xml[pair.first] = pair.second;
        auto &content = xml.asContent();
        for (szt i = 0; i < getChildCount(); i++)
        {
            auto child = getChild(i);
            if (child)
            {
                auto options = getOptions(*child);
                auto child_xml = cacto::toXml(child);
                child_xml["options:coords"] = toString(options->getCoords());
                child_xml["options:relation"] = toString(options->getRelation());
                content.push_back(std::move(child_xml));
            }
        }
        return std::move(xml);
    }

    void Skeleton::fromXml(const XmlValue &xml)
    {
        clearChildren();
        setId(xml.getAttribute("id"));
        m_transformable = toTransformable(xml);
        if (xml.isTag())
            for (auto &item : xml.asContent())
            {
                Node *node = cacto::fromXml<Node>(item);
                if (node)
                {
                    auto child = dynamic_cast<ChildNode *>(node);
                    if (child)
                    {
                        std::shared_ptr<ChildNode> ptr{child};
                        sf::Vector2f coords = toVector(item.getAttribute("options:coords", "0,0"));
                        Skeleton::Relation relation = toRelation(item.getAttribute("options:relation", "Body"));
                        append(ptr,
                               Options()
                                   .setCoords(coords)
                                   .setRelation(relation));
                    }
                    else
                        delete node;
                }
            }
    }

    Skeleton::Skeleton()
        : m_transformable(),
          m_id(),
          m_parent(),
          m_holders()
    {
    }

    Skeleton::~Skeleton()
    {
        detach();
        clearChildren();
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
                    cacto::draw(*holder.child, target, _states);
                }
                break;
                case Relation::Bone:
                {
                    auto _states = states;
                    _states.transform.translate(m_transformable.getTransform().transformPoint(holder.options.getCoords()));
                    cacto::draw(*holder.child, target, _states);
                }
                break;
                default:
                    break;
                }
            }
        }
    }

    const sf::Vector2f &Skeleton::Options::getCoords() const
    {
        return m_coords;
    }

    Skeleton::Options &Skeleton::Options::setCoords(const sf::Vector2f &value)
    {
        m_coords = value;
        return *this;
    }

    Skeleton::Relation Skeleton::Options::getRelation() const
    {
        return m_relation;
    }

    Skeleton::Options &Skeleton::Options::setRelation(Relation value)
    {
        m_relation = value;
        return *this;
    }

    Skeleton::Options::Options(const sf::Vector2f &coords, Relation relation)
        : m_coords(coords),
          m_relation(relation)
    {
    }

    Skeleton::Options::~Options() = default;

    std::string toString(Skeleton::Relation relation)
    {
        if (relation == Skeleton::Relation::Body)
            return "Body";
        else if (relation == Skeleton::Relation::Bone)
            return "Bone";
        else
            throw std::runtime_error("Unsupported relation");
    }

    Skeleton::Relation toRelation(const std::string &string)
    {
        if (string == "Body")
            return Skeleton::Relation::Body;
        else if (string == "Bone")
            return Skeleton::Relation::Bone;
        else
            throw std::runtime_error("Unsupported relation");
    }

    namespace skeleton
    {

        XmlValue XmlConverter::toXml(const Node *const value) const
        {
            const Skeleton *skeleton = nullptr;
            if (value && typeid(*value) == typeid(Skeleton) && (skeleton = dynamic_cast<const Skeleton *>(value)))
            {
                auto xml = skeleton->toXml();
                return std::move(xml);
            }
            return nullptr;
        }

        Node *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.getKind() == XmlValue::Tag && xml.getName() == "Skeleton")
            {
                auto skeleton = new Skeleton();
                skeleton->fromXml(xml);
                return skeleton;
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }
}