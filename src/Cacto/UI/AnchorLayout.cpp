#include <stdexcept>
#include <algorithm>
#include <Cacto/UI/AnchorLayout.hpp>

namespace cacto
{

    szt AnchorLayout::getChildCount() const
    {
        auto count = m_holders.size();
        return count;
    }

    Node *const AnchorLayout::getChild(szt index) const
    {
        if (index < m_holders.size())
        {
            auto child = m_holders[index].child;
            return child;
        }
        return nullptr;
    }

    Box::Anchor AnchorLayout::getHorizontalAnchor(const Node &child) const
    {
        auto holder = getHolder(child);
        if (!holder)
            throw std::runtime_error("The node is not a child");
        return holder->hAnchor;
    }

    void AnchorLayout::setHorizontalAnchor(Node &child, Anchor value)
    {
        auto holder = getHolder(child);
        if (!holder)
            throw std::runtime_error("The node is not a child");
        holder->hAnchor = value;
    }

    Box::Anchor AnchorLayout::getVerticalAnchor(const Node &child) const
    {
        auto holder = getHolder(child);
        if (!holder)
            throw std::runtime_error("The node is not a child");
        return holder->vAnchor;
    }

    void AnchorLayout::setVerticalAnchor(Node &child, Anchor value)
    {
        auto holder = getHolder(child);
        if (!holder)
            throw std::runtime_error("The node is not a child");
        holder->vAnchor = value;
    }

    void AnchorLayout::append(Node &child)
    {
        Node::link(*this, child);
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
        for (auto &holder : m_holders)
            Node::unlink(*this, *holder.child);
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

    const AnchorLayout::Holder *const AnchorLayout::getHolder(const Node &node) const
    {
        for (auto &holder : m_holders)
        {
            if (holder.child == &node)
                return &holder;
        }
        return nullptr;
    }

    AnchorLayout::Holder *const AnchorLayout::getHolder(const Node &node)
    {
        for (auto &holder : m_holders)
        {
            if (holder.child == &node)
                return &holder;
        }
        return nullptr;
    }

    void AnchorLayout::onAppend(Node &child)
    {
        auto holder = getHolder(child);
        if (holder != nullptr)
            throw std::runtime_error("This node can not has more child nodes");
        Holder _holder{};
        _holder.child = &child;
        _holder.hAnchor = Start;
        _holder.vAnchor = Start;
        m_holders.push_back(_holder);
    }

    void AnchorLayout::onRemove(Node &child)
    {
        auto holder = getHolder(child);
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child node");
        m_holders.erase(std::find_if(m_holders.begin(), m_holders.end(), [holder](auto &it)
                                     { return &it == holder; }));
    }

    sf::Vector2f AnchorLayout::onCompact(const sf::Vector2f &contentSize)
    {
        auto _contentSize = contentSize;
        if (m_holders.size() > 0)
        {
            for (auto &holder : m_holders)
            {
                auto size = InflatableNode::compact(*holder.child, contentSize);
                _contentSize.x = std::max(size.x, _contentSize.x);
                _contentSize.y = std::max(size.y, _contentSize.y);
            }
        }
        auto boxSize = Block::onCompact(_contentSize);
        return boxSize;
    }

    sf::Vector2f AnchorLayout::onInflate(const sf::Vector2f &containerSize)
    {
        auto boxSize = Block::onInflate(containerSize);
        if (m_holders.size() > 0)
        {
            auto margin = getMargin();
            auto padding = getPadding();
            sf::Vector2f _containerSize{boxSize.x - margin.getHorizontal() - padding.getHorizontal(),
                                        boxSize.y - margin.getVertical() - padding.getVertical()};

            for (auto &holder : m_holders)
            {
                auto _boxSize = InflatableNode::inflate(*holder.child, _containerSize);
                holder.boxSize = _boxSize;
            }
        }
        return boxSize;
    }

    void AnchorLayout::onPlace(const sf::Vector2f &position)
    {
        Block::onPlace(position);
        if (m_holders.size() > 0)
        {
            auto padding = getPadding();
            sf::Vector2f containerSize{
                getWidth() - padding.getHorizontal(),
                getHeight() - padding.getVertical()};
            sf::Vector2f contentPosition{
                getLeft() + padding.left,
                getTop() + padding.top};
            for (auto &holder : m_holders)
            {
                auto &boxSize = holder.boxSize;
                auto _contentPosition = contentPosition;
                switch (holder.hAnchor)
                {
                case Start:
                    break;
                case End:
                    _contentPosition.x += containerSize.x - boxSize.x;
                    break;
                case Center:
                    _contentPosition.x += (containerSize.x - boxSize.x) / 2;
                    break;
                }
                switch (holder.vAnchor)
                {
                case Start:
                    break;
                case End:
                    _contentPosition.y += containerSize.y - boxSize.y;
                    break;
                case Center:
                    _contentPosition.y += (containerSize.y - boxSize.y) / 2;
                    break;
                }
                InflatableNode::place(*holder.child, _contentPosition);
            }
        }
    }

}