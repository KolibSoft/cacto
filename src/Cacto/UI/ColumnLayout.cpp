#include <stdexcept>
#include <algorithm>
#include <Cacto/UI/ColumnLayout.hpp>

namespace cacto
{

    ColumnLayout::Anchor ColumnLayout::getHorizontalAnchor(const Node &child) const
    {
        auto holder = dynamic_cast<const ColumnHolder *>(getHolder(child));
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child");
        return holder->hAnchor;
    }

    void ColumnLayout::setHorizontalAnchor(Node &child, Anchor value)
    {
        auto holder = dynamic_cast<ColumnHolder *>(getHolder(child));
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child");
        holder->hAnchor = value;
    }

    ColumnLayout::Anchor ColumnLayout::getVerticalAnchor() const
    {
        return m_vAnchor;
    }

    void ColumnLayout::setVerticalAnchor(Anchor value)
    {
        m_vAnchor = value;
    }

    ColumnLayout::Direction ColumnLayout::getDirection() const
    {
        return m_direction;
    }

    void ColumnLayout::setDirection(Direction value)
    {
        m_direction = value;
    }

    f32t ColumnLayout::getHorizontalWeight(const Node &child) const
    {
        auto holder = dynamic_cast<const ColumnHolder *>(getHolder(child));
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child");
        return holder->hWeight;
    }

    void ColumnLayout::setHorizontalWeight(Node &child, f32t value)
    {
        auto holder = dynamic_cast<ColumnHolder *>(getHolder(child));
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child");
        holder->hWeight = value;
    }

    f32t ColumnLayout::getVerticalWeight(const Node &child) const
    {
        auto holder = dynamic_cast<const ColumnHolder *>(getHolder(child));
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child");
        return holder->vWeight;
    }

    void ColumnLayout::setVerticalWeight(Node &child, f32t value)
    {
        auto holder = dynamic_cast<ColumnHolder *>(getHolder(child));
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child");
        holder->vWeight = value;
    }

    ColumnLayout::ColumnLayout()
        : m_vAnchor(Start),
          m_direction(Forward) {}

    ColumnLayout::~ColumnLayout() = default;

    ColumnLayout::ColumnLayout(const ColumnLayout &other)
        : Layout(other),
          m_vAnchor(other.m_vAnchor),
          m_direction(other.m_direction),
          m_length(0)
    {
    }

    ColumnLayout &ColumnLayout::operator=(const ColumnLayout &other)
    {
        Layout::operator=(other);
        m_vAnchor = other.m_vAnchor;
        m_direction = other.m_direction;
        m_length = other.m_length;
        return *this;
    }

    ColumnLayout::ColumnHolder *ColumnLayout::onHold(Node &child) const
    {
        auto holder = new ColumnHolder(child);
        return holder;
    }

    sf::Vector2f ColumnLayout::onCompact()
    {
        sf::Vector2f contentSize{0, 0};
        if (getChildCount() > 0)
        {
            f32t length = 0;
            for (szt i = 0; i < getChildCount(); i++)
            {
                auto holder = getHolder(i);
                auto childSize = InflatableNode::compact(holder->child);
                length += childSize.y;
                contentSize.x = std::max(childSize.x, contentSize.x);
            }
            m_length = length;
            contentSize.y = std::max(length, contentSize.y);
        }
        auto size = Block::compactContent(contentSize);
        return size;
    }

    sf::Vector2f ColumnLayout::onInflate(const sf::Vector2f &containerSize)
    {
        auto size = Block::onInflate(containerSize);
        if (getChildCount() > 0)
        {
            f32t length = 0;
            auto contentBox = getContentBox();
            sf::Vector2f contentSize{contentBox.getWidth(), contentBox.getHeight()};
            for (szt i = 0; i < getChildCount(); i++)
            {
                auto holder = dynamic_cast<ColumnHolder *>(getHolder(i));
                auto childSize = InflatableNode::inflate(holder->child, {contentSize.x * holder->hWeight, contentSize.y * holder->vWeight});
                holder->size = childSize;
                length += childSize.y;
            }
            m_length = length;
        }
        return size;
    }

    void ColumnLayout::onPlace(const sf::Vector2f &position)
    {
        Block::onPlace(position);
        if (getChildCount() > 0)
        {
            auto contentBox = getContentBox();
            sf::Vector2f contentSize{contentBox.getWidth(), contentBox.getHeight()};
            sf::Vector2f contentPosition{contentBox.getLeft(), contentBox.getTop()};
            f32t offset = 0;
            auto place = [&](ColumnHolder *holder)
            {
                auto &childSize = holder->size;
                auto _contentPosition{contentPosition};
                _contentPosition.y += offset;
                switch (holder->hAnchor)
                {
                case Start:
                    break;
                case End:
                    _contentPosition.x += contentSize.x - childSize.x;
                    break;
                case Center:
                    _contentPosition.x += (contentSize.x - childSize.x) / 2;
                    break;
                }
                InflatableNode::place(holder->child, _contentPosition);
                offset += holder->size.y;
            };
            switch (m_direction)
            {
            case Forward:
                switch (m_vAnchor)
                {
                case Start:
                    break;
                case End:
                    offset += contentSize.y - m_length;
                    break;
                case Center:
                    offset += (contentSize.y - m_length) / 2;
                    break;
                }
                for (szt i = 0; i < getChildCount(); i++)
                {
                    auto holder = dynamic_cast<ColumnHolder *>(getHolder(i));
                    place(holder);
                }
                break;
            case Reverse:
                switch (m_vAnchor)
                {
                case Start:
                    offset += contentSize.y - m_length;
                    break;
                case End:
                    break;
                case Center:
                    offset += (contentSize.y - m_length) / 2;
                    break;
                }
                for (szt i = getChildCount(); i > 0; i--)
                {
                    auto holder = dynamic_cast<ColumnHolder *>(getHolder(i - 1));
                    place(holder);
                }
                break;
            }
        }
    }

    ColumnLayout::ColumnHolder::ColumnHolder(Node &child)
        : Holder(child),
          hAnchor(Start),
          hWeight(1),
          vWeight(0),
          size()
    {
    }

    ColumnLayout::ColumnHolder::~ColumnHolder() = default;

}