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

    Shared<Node> Skeleton::getParent() const
    {
        return m_parent.lock();
    }

    szt Skeleton::getChildCount() const
    {
        return m_holders.size();
    }

    Shared<Node> Skeleton::getChild(szt index) const
    {
        if (index >= m_holders.size())
            return nullptr;
        auto &holder = m_holders.at(index);
        return holder.child;
    }

    const Skeleton::Options &Skeleton::getOptions(const Shared<const Node> &child) const
    {
        for (auto &holder : m_holders)
            if (holder.child == child)
                return holder.options;
        throw std::runtime_error("The node is not a child");
    }

    Skeleton::Options &Skeleton::getOptions(const Shared<const Node> &child)
    {
        for (auto &holder : m_holders)
            if (holder.child == child)
                return holder.options;
        throw std::runtime_error("The node is not a child");
    }

    Skeleton &Skeleton::append(const Shared<Node> &child, const Options &options)
    {
        Node::link(as<Node>(), child);
        auto &holder = m_holders.back();
        holder.options = options;
        return *this;
    }

    void Skeleton::remove(const Shared<Node> &child)
    {
        Node::unlink(as<Node>(), child);
    }

    Skeleton::Skeleton()
        : m_id(),
          m_parent(),
          m_holders()
    {
    }

    Skeleton::~Skeleton() = default;

    void Skeleton::onAttach(const Shared<Node> &parent)
    {
        m_parent = parent;
    }

    void Skeleton::onDetach(const Shared<Node> &parent)
    {
        m_parent.reset();
    }

    void Skeleton::onAppend(const Shared<Node> &child)
    {
        holder holder{};
        holder.child = child;
        holder.options = {};
        m_holders.push_back(holder);
    }

    void Skeleton::onRemove(const Shared<Node> &child)
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
                switch (holder.options.getRelation())
                {
                case Relation::Body:
                {
                    auto _states = states;
                    _states.transform *= getTransform();
                    _states.transform.translate(holder.options.getCoords());
                    DrawNode::draw(holder.child, target, _states);
                }
                break;
                case Relation::Bone:
                {
                    auto _states = states;
                    _states.transform.translate(getTransform().transformPoint(holder.options.getCoords()));
                    DrawNode::draw(holder.child, target, _states);
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
        XmlValue xml = toXml((sf::Transformable &)skeleton);
        xml.setName("Skeleton");
        xml["id"] = skeleton.getId();
        auto &content = xml.asContent();
        for (szt i = 0; i < skeleton.getChildCount(); i++)
        {
            auto child = skeleton.getChild(i);
            if (child)
            {
                auto &options = skeleton.getOptions(child);
                auto child_xml = cacto::toXml(child);
                child_xml["options:coords"] = cacto::toString(options.getCoords());
                child_xml["options:relation"] = cacto::toString(options.getRelation());
                content.push_back(std::move(child_xml));
            }
        }
        return std::move(xml);
    }

    void fromXml(Skeleton &skeleton, const XmlValue &xml)
    {
        fromXml((sf::Transformable &)skeleton, xml);
        skeleton.setId(xml.getAttribute("id"));
        if (xml.isTag())
            for (auto &item : xml.asContent())
            {
                Shared<Node> node = nullptr;
                cacto::fromXml(node, item);
                if (node)
                {
                    sf::Vector2f coords{};
                    cacto::fromString(coords, item.getAttribute("options:coords", "0,0"));
                    Skeleton::Relation relation{};
                    cacto::fromString(relation, item.getAttribute("options:relation", "Body"));
                    skeleton
                        .append(node,
                                Skeleton::Options()
                                    .setCoords(coords)
                                    .setRelation(relation));
                }
            }
    }

    namespace skeleton
    {

        XmlValue XmlConverter::toXml(const Shared<const Node> &value) const
        {
            Shared<const Skeleton> skeleton = nullptr;
            auto ptr = value.get();
            if (value && typeid(*ptr) == typeid(Skeleton) && (skeleton = std::dynamic_pointer_cast<const Skeleton>(value)))
            {
                auto xml = cacto::toXml(*skeleton);
                return std::move(xml);
            }
            return nullptr;
        }

        Shared<Node> XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.getKind() == XmlValue::Tag && xml.getName() == "Skeleton")
            {
                auto skeleton = std::make_shared<Skeleton>();
                cacto::fromXml(*skeleton, xml);
                return std::move(skeleton);
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }
}