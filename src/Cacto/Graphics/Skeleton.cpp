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

    const sf::Vector2f &Skeleton::getCoord(Node &child) const
    {
        auto index = getChildIndex(child);
        if (index < 0)
            throw std::runtime_error("The node is not a child");
        auto &value = m_holders.at(index).getCoord();
        return value;
    }

    void Skeleton::setCoord(Node &child, const sf::Vector2f &value)
    {
        auto index = getChildIndex(child);
        if (index < 0)
            throw std::runtime_error("The node is not a child");
        m_holders.at(index).setCoord(value);
    }

    Skeleton::Relation Skeleton::getRelation(Node &child) const
    {
        auto index = getChildIndex(child);
        if (index < 0)
            throw std::runtime_error("The node is not a child");
        auto value = m_holders.at(index).getRelation();
        return value;
    }

    void Skeleton::setRelation(Node &child, Relation value)
    {
        auto index = getChildIndex(child);
        if (index < 0)
            throw std::runtime_error("The node is not a child");
        m_holders.at(index).setRelation(value);
    }

    Skeleton::Holder &Skeleton::append(Node &child)
    {
        Node::link(*this, child);
        return m_holders.back();
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
        : Transformable(other)
    {
    }

    Skeleton &Skeleton::operator=(const Skeleton &other)
    {
        sf::Transformable::operator=(other);
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
        Holder holder{child};
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

        Holder::Holder(Node &node)
            : node::Holder(node),
              m_coord(),
              m_relation(Skeleton::Body)
        {
        }

        Holder::~Holder() = default;

    }

}