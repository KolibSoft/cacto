#include <stdexcept>
#include <Cacto/UI/AnchorLayout.hpp>

namespace cacto
{

    szt AnchorLayout::getChildCount() const
    {
        return m_holders.size();
    }

    Node *const AnchorLayout::getChild(szt index) const
    {
        if (index >= m_holders.size())
            return nullptr;
        auto &holder = m_holders.at(index);
        return &holder.getNode();
    }

    Box::Anchor AnchorLayout::getHorizontalAnchor(const Node &child) const
    {
        auto index = getChildIndex(child);
        if (index < 0)
            throw std::runtime_error("The node is not a child");
        auto &holder = m_holders.at(index);
        return holder.getHorizontalAnchor();
    }

    AnchorLayout &AnchorLayout::setHorizontalAnchor(Node &child, Anchor value)
    {
        auto index = getChildIndex(child);
        if (index < 0)
            throw std::runtime_error("The node is not a child");
        auto &holder = m_holders.at(index);
        holder.setHorizontalAnchor(value);
        return *this;
    }

    Box::Anchor AnchorLayout::getVerticalAnchor(const Node &child) const
    {
        auto index = getChildIndex(child);
        if (index < 0)
            throw std::runtime_error("The node is not a child");
        auto &holder = m_holders.at(index);
        return holder.getVerticalAnchor();
    }

    AnchorLayout &AnchorLayout::setVerticalAnchor(Node &child, Anchor value)
    {
        auto index = getChildIndex(child);
        if (index < 0)
            throw std::runtime_error("The node is not a child");
        auto &holder = m_holders.at(index);
        holder.setVerticalAnchor(value);
        return *this;
    }

    f32t AnchorLayout::getHorizontalWeight(const Node &child) const
    {
        auto index = getChildIndex(child);
        if (index < 0)
            throw std::runtime_error("The node is not a child");
        auto &holder = m_holders.at(index);
        return holder.getHorizontalWeight();
    }

    AnchorLayout &AnchorLayout::setHorizontalWeight(Node &child, f32t value)
    {
        auto index = getChildIndex(child);
        if (index < 0)
            throw std::runtime_error("The node is not a child");
        auto &holder = m_holders.at(index);
        holder.setHorizontalWeight(value);
        return *this;
    }

    f32t AnchorLayout::getVerticalWeight(const Node &child) const
    {
        auto index = getChildIndex(child);
        if (index < 0)
            throw std::runtime_error("The node is not a child");
        auto &holder = m_holders.at(index);
        return holder.getVerticalWeight();
    }

    AnchorLayout &AnchorLayout::setVerticalWeight(Node &child, f32t value)
    {
        auto index = getChildIndex(child);
        if (index < 0)
            throw std::runtime_error("The node is not a child");
        auto &holder = m_holders.at(index);
        holder.setVerticalWeight(value);
        return *this;
    }

    AnchorLayout::Holder &AnchorLayout::append(Node &child)
    {
        Node::link(*this, child);
        return m_holders.back();
    }

    void AnchorLayout::remove(Node &child)
    {
        Node::unlink(*this, child);
    }

    AnchorLayout::AnchorLayout()
        : m_holders()
    {
    }

    AnchorLayout::~AnchorLayout()
    {
        while (m_holders.size() > 0)
            Node::unlink(*this, m_holders.back().getNode());
    }

    AnchorLayout::AnchorLayout(const AnchorLayout &other)
        : Block(other),
          m_holders()
    {
    }

    AnchorLayout &AnchorLayout::operator=(const AnchorLayout &other)
    {
        Block::operator=(other);
        return *this;
    }

    void AnchorLayout::onAppend(Node &child)
    {
        Holder holder{child};
        m_holders.push_back(holder);
    }

    void AnchorLayout::onRemove(Node &child)
    {
        auto index = getChildIndex(child);
        m_holders.erase(m_holders.begin() + index);
    }

    void AnchorLayout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        drawBlock(target, states);
        drawChildren(target, states);
    }

    sf::Vector2f AnchorLayout::onInflate(const sf::Vector2f &containerSize)
    {
        auto size = inflateBlock(containerSize);
        if (m_holders.size() > 0)
        {
            auto contentBox = getContentBox();
            sf::Vector2f contentSize{contentBox.getWidth(), contentBox.getHeight()};
            for (auto &holder : m_holders)
                holder.inflate({contentSize.x * holder.getHorizontalWeight(), contentSize.y * holder.getVerticalWeight()});
        }
        return size;
    }

    void AnchorLayout::onPlace(const sf::Vector2f &position)
    {
        placeBlock(position);
        if (m_holders.size() > 0)
        {
            auto contentBox = getContentBox();
            for (auto &holder : m_holders)
            {
                auto _contentBox = contentBox;
                auto &childBox = holder.getBox();
                _contentBox.setWidth(childBox.getWidth(), holder.getHorizontalAnchor());
                _contentBox.setHeight(childBox.getHeight(), holder.getVerticalAnchor());
                holder.place({_contentBox.getLeft(), _contentBox.getTop()});
            }
        }
    }

    namespace anchor_layout
    {

        AnchorLayout::Anchor Holder::getHorizontalAnchor() const
        {
            return m_hAnchor;
        }

        Holder &Holder::setHorizontalAnchor(AnchorLayout::Anchor value)
        {
            m_hAnchor = value;
            return *this;
        }

        AnchorLayout::Anchor Holder::getVerticalAnchor() const
        {
            return m_vAnchor;
        }

        Holder &Holder::setVerticalAnchor(AnchorLayout::Anchor value)
        {
            m_vAnchor = value;
            return *this;
        }

        f32t Holder::getHorizontalWeight() const
        {
            return m_hWeight;
        }

        Holder &Holder::setHorizontalWeight(f32t value)
        {
            m_hWeight = value;
            return *this;
        }

        f32t Holder::getVerticalWeight() const
        {
            return m_vWeight;
        }

        Holder &Holder::setVerticalWeight(f32t value)
        {
            m_vWeight = value;
            return *this;
        }

        Holder::Holder(Node &node)
            : layout::Holder(node),
              m_hAnchor(AnchorLayout::Start),
              m_vAnchor(AnchorLayout::Start),
              m_hWeight(1),
              m_vWeight(1)
        {
        }

        Holder::~Holder() = default;

    }

}