#include <stdexcept>
#include <Cacto/Core/Utils.hpp>
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

    const Skeleton::Options *const Skeleton::getOptions(Node &child) const
    {
        for (auto &holder : m_holders)
            if (holder.child == &child)
                return &holder.options;
        return nullptr;
    }

    Skeleton::Options *const Skeleton::getOptions(Node &child)
    {
        for (auto &holder : m_holders)
            if (holder.child == &child)
                return &holder.options;
        return nullptr;
    }

    Skeleton &Skeleton::append(Node &child, const Options &options, bool internal)
    {
        Node::link(*this, child);
        auto &holder = m_holders.back();
        holder.options = options;
        holder.internal = internal;
        return *this;
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
        {
            auto &holder = m_holders.back();
            auto child = holder.child;
            auto internal = holder.internal;
            Node::unlink(*this, *child);
            if (internal)
                delete child;
        }
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
        holder holder{};
        holder.child = &child;
        holder.options = {};
        holder.internal = false;
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
                switch (holder.options.getRelation())
                {
                case Relation::Body:
                {
                    auto _states = states;
                    _states.transform *= getTransform();
                    _states.transform.translate(holder.options.getCoords());
                    DrawNode::draw(*holder.child, target, _states);
                }
                break;
                case Relation::Bone:
                {
                    auto _states = states;
                    _states.transform.translate(getTransform().transformPoint(holder.options.getCoords()));
                    DrawNode::draw(*holder.child, target, _states);
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
        XmlValue xml{"Skeleton", {}};
        auto &content = xml.asContent();
        for (szt i = 0; i < skeleton.getChildCount(); i++)
        {
            auto child = skeleton.getChild(i);
            auto options = skeleton.getOptions(*child);
            auto _xml = cacto::toXml(child);
            _xml["options:coords"] = cacto::toString(options->getCoords());
            _xml["options:relation"] = cacto::toString(options->getRelation());
            content.push_back(_xml);
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
                sf::Vector2f coords{};
                cacto::fromString(coords, item.getAttribute("options:coords", "0,0"));
                Skeleton::Relation relation{};
                cacto::fromString(relation, item.getAttribute("options:relation", "Body"));
                skeleton
                    .append(*node,
                            Skeleton::Options()
                                .setCoords(coords)
                                .setRelation(relation),
                            true);
            }
    }

    namespace skeleton
    {

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