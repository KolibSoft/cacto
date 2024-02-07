#include <stdexcept>
#include <SFML/Graphics/RenderStates.hpp>
#include <Cacto/Core/VectorUtils.hpp>
#include <Cacto/Graphics/NodeUtils.hpp>
#include <Cacto/Graphics/VectorUtils.hpp>
#include <Cacto/Graphics/TransformableUtils.hpp>
#include <Cacto/Graphics/Skeleton.hpp>

namespace cacto
{

    std::string toString(SkeletonRelation relation)
    {
        if (relation == SkeletonRelation::Body)
            return "Body";
        else if (relation == SkeletonRelation::Bone)
            return "Bone";
        else
            throw std::runtime_error("Unsupported relation");
    }

    SkeletonRelation toRelation(const std::string &string)
    {
        if (string == "Body")
            return SkeletonRelation::Body;
        else if (string == "Bone")
            return SkeletonRelation::Bone;
        else
            throw std::runtime_error("Unsupported relation");
    }

    const sf::Vector2f &SkeletonOptions::getCoords() const
    {
        return m_coords;
    }

    SkeletonOptions &SkeletonOptions::setCoords(const sf::Vector2f &value)
    {
        m_coords = value;
        return *this;
    }

    SkeletonRelation SkeletonOptions::getRelation() const
    {
        return m_relation;
    }

    SkeletonOptions &SkeletonOptions::setRelation(SkeletonRelation value)
    {
        m_relation = value;
        return *this;
    }

    SkeletonOptions::SkeletonOptions(const sf::Vector2f &coords, SkeletonRelation relation)
        : m_coords(coords),
          m_relation(relation)
    {
    }

    SkeletonOptions::~SkeletonOptions() = default;

    Skeleton &&Skeleton::setOrigin(const sf::Vector2f &value)
    {
        sf::Transformable::setOrigin(value);
        return std::move(*this);
    }

    Skeleton &&Skeleton::setPosition(const sf::Vector2f &value)
    {
        sf::Transformable::setPosition(value);
        return std::move(*this);
    }

    Skeleton &&Skeleton::setScale(const sf::Vector2f &value)
    {
        sf::Transformable::setScale(value);
        return std::move(*this);
    }

    Skeleton &&Skeleton::setRotation(sf::Angle value)
    {
        sf::Transformable::setRotation(value);
        return std::move(*this);
    }

    Skeleton &&Skeleton::move(const sf::Vector2f &offset)
    {
        sf::Transformable::move(offset);
        return std::move(*this);
    }

    Skeleton &&Skeleton::scale(const sf::Vector2f &factors)
    {
        sf::Transformable::scale(factors);
        return std::move(*this);
    }

    Skeleton &&Skeleton::rotate(const sf::Angle &angle)
    {
        sf::Transformable::rotate(angle);
        return std::move(*this);
    }

    const std::string &Skeleton::getId() const
    {
        return m_id;
    }

    Skeleton &&Skeleton::setId(const std::string &value)
    {
        m_id = value;
        return std::move(*this);
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

    const SkeletonOptions *const Skeleton::getOptions(const Node &child) const
    {
        for (auto &holder : m_holders)
            if (holder.child == &child)
                return &holder.options;
        return nullptr;
    }

    SkeletonOptions *const Skeleton::getOptions(const Node &child)
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
        auto &holder = m_holders.emplace_back();
        holder.child = &child;
        holder.options = {};
        holder.owned = false;
        child.attach(*this);
    }

    Skeleton &&Skeleton::append(ChildNode &child, const SkeletonOptions &options)
    {
        append(child);
        m_holders.back().options = options;
        return std::move(*this);
    }

    Skeleton &&Skeleton::append(ChildNode &&child, const SkeletonOptions &options)
    {
        auto _child = dynamic_cast<ChildNode *>(child.acquire());
        append(*_child, options);
        m_holders.back().owned = true;
        return std::move(*this);
    }

    void Skeleton::remove(ChildNode &child)
    {
        auto index = getChildIndex(child);
        if (index >= 0)
        {
            auto holder = m_holders[index];
            m_holders.erase(m_holders.begin() + index);
            child.detach();
            if (holder.owned)
                delete holder.child;
        }
    }

    Skeleton *Skeleton::clone() const
    {
        auto skeleton = new Skeleton(*this);
        return skeleton;
    }

    Skeleton *Skeleton::acquire()
    {
        auto skeleton = new Skeleton(std::move(*this));
        return skeleton;
    }

    Skeleton::Skeleton()
        : sf::Transformable(),
          m_id(),
          m_holders(),
          m_parent()
    {
    }

    Skeleton::~Skeleton()
    {
        detach();
        clearChildren();
    }

    Skeleton::Skeleton(const Skeleton &other)
        : Skeleton()
    {
        *this = other;
    }

    Skeleton &Skeleton::operator=(const Skeleton &other)
    {
        clearChildren();
        sf::Transformable::operator=(other);
        m_id = other.m_id;
        for (auto &holder : other.m_holders)
        {
            auto child = dynamic_cast<ChildNode *>(holder.child->clone());
            if (child)
            {
                append(*child, holder.options);
                m_holders.back().owned = true;
            }
        }
        return *this;
    }

    Skeleton::Skeleton(Skeleton &&other)
        : Skeleton()
    {
        *this = std::move(other);
    }

    Skeleton &Skeleton::operator=(Skeleton &&other)
    {
        clearChildren();
        sf::Transformable::operator=(std::move(other));
        m_id = std::move(other.m_id);
        m_holders = std::move(other.m_holders);
        for (auto &holder : m_holders)
        {
            holder.child->detach();
            holder.child->attach(*this);
        }
        other.detach();
        return *this;
    }

    void Skeleton::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (m_holders.size() > 0)
        {
            for (auto &holder : m_holders)
            {
                switch (holder.options.getRelation())
                {
                case SkeletonRelation::Body:
                {
                    auto _states = states;
                    _states.transform *= getTransform();
                    _states.transform.translate(holder.options.getCoords());
                    cacto::draw(*holder.child, target, _states);
                }
                break;
                case SkeletonRelation::Bone:
                {
                    auto _states = states;
                    _states.transform.translate(getTransform().transformPoint(holder.options.getCoords()));
                    cacto::draw(*holder.child, target, _states);
                }
                break;
                default:
                    break;
                }
            }
        }
    }

    XmlValue toXml(const Skeleton &skeleton)
    {
        XmlValue xml{"Skeleton", {}};
        xml["id"] = skeleton.getId();
        auto txml = toXml((const sf::Transformable &)skeleton);
        for (auto &pair : txml.asTag().attributes)
            xml[pair.first] = pair.second;
        auto &content = xml.asTag().content;
        for (szt i = 0; i < skeleton.getChildCount(); i++)
        {
            auto child = skeleton.getChild(i);
            if (child)
            {
                auto options = skeleton.getOptions(*child);
                auto child_xml = toXml(child);
                child_xml["options:coords"] = toString(options->getCoords());
                child_xml["options:relation"] = toString(options->getRelation());
                content.push_back(std::move(child_xml));
            }
        }
        return std::move(xml);
    }

    Skeleton toSkeleton(const XmlValue &xml)
    {
        Skeleton skeleton{};
        skeleton.setId(xml.getAttribute("id"));
        (sf::Transformable &)skeleton = toTransformable(xml);
        if (xml.isTag())
            for (auto &item : xml.asTag().content)
            {
                Node *node = cacto::fromXml<Node>(item);
                if (node)
                {
                    auto child = dynamic_cast<ChildNode *>(node);
                    if (child)
                    {
                        sf::Vector2f coords = toVector(item.getAttribute("options:coords", "0,0"));
                        SkeletonRelation relation = toRelation(item.getAttribute("options:relation", "Body"));
                        skeleton.append(std::move(*child),
                                        SkeletonOptions()
                                            .setCoords(coords)
                                            .setRelation(relation));
                    }
                    delete node;
                }
            }
        return std::move(skeleton);
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
            if (xml.isTag() && xml.getName() == "Skeleton")
            {
                auto skeleton = new Skeleton();
                *skeleton = toSkeleton(xml);
                return skeleton;
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }
}