#include <stdexcept>
#include <algorithm>
#include <Cacto/UI/RowLayout.hpp>

namespace cacto
{

    RowLayout::Anchor RowLayout::getVerticalAnchor(const Node &child) const
    {
        auto holder = dynamic_cast<const RowHolder *>(getHolder(child));
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child");
        return holder->vAnchor;
    }

    void RowLayout::setVerticalAnchor(Node &child, Anchor value)
    {
        auto holder = dynamic_cast<RowHolder *>(getHolder(child));
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child");
        holder->vAnchor = value;
    }

    RowLayout::Anchor RowLayout::getHorizontalAnchor() const
    {
        return m_hAnchor;
    }

    void RowLayout::setHorizontalAnchor(Anchor value)
    {
        m_hAnchor = value;
    }

    RowLayout::Direction RowLayout::getDirection() const
    {
        return m_direction;
    }

    void RowLayout::setDirection(Direction value)
    {
        m_direction = value;
    }

    f32t RowLayout::getHorizontalWeight(const Node &child) const
    {
        auto holder = dynamic_cast<const RowHolder *>(getHolder(child));
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child");
        return holder->hWeight;
    }

    void RowLayout::setHorizontalWeight(Node &child, f32t value)
    {
        auto holder = dynamic_cast<RowHolder *>(getHolder(child));
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child");
        holder->hWeight = value;
    }

    f32t RowLayout::getVerticalWeight(const Node &child) const
    {
        auto holder = dynamic_cast<const RowHolder *>(getHolder(child));
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child");
        return holder->vWeight;
    }

    void RowLayout::setVerticalWeight(Node &child, f32t value)
    {
        auto holder = dynamic_cast<RowHolder *>(getHolder(child));
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child");
        holder->vWeight = value;
    }

    RowLayout::RowLayout()
        : m_hAnchor(Start),
          m_direction(Forward) {}

    RowLayout::~RowLayout() = default;

    RowLayout::RowLayout(const RowLayout &other)
        : Layout(other),
          m_hAnchor(other.m_hAnchor),
          m_direction(other.m_direction),
          m_length(0)
    {
    }

    RowLayout &RowLayout::operator=(const RowLayout &other)
    {
        Layout::operator=(other);
        m_hAnchor = other.m_hAnchor;
        m_direction = other.m_direction;
        m_length = other.m_length;
        return *this;
    }

    RowLayout::RowHolder *RowLayout::onHold(Node &child) const
    {
        auto holder = new RowHolder(child);
        return holder;
    }

    sf::Vector2f RowLayout::onCompact()
    {
        sf::Vector2f contentSize{0, 0};
        if (getChildCount() > 0)
        {
            f32t length = 0;
            for (szt i = 0; i < getChildCount(); i++)
            {
                auto holder = getHolder(i);
                auto childSize = InflatableNode::compact(holder->child);
                length += childSize.x;
                contentSize.y = std::max(childSize.y, contentSize.y);
            }
            m_length = length;
            contentSize.x = std::max(length, contentSize.x);
        }
        auto size = compactBlock(contentSize);
        return size;
    }

    sf::Vector2f RowLayout::onInflate(const sf::Vector2f &containerSize)
    {
        auto size = inflateBlock(containerSize);
        if (getChildCount() > 0)
        {
            f32t length = 0;
            auto contentBox = getContentBox();
            sf::Vector2f contentSize{contentBox.getWidth(), contentBox.getHeight()};
            for (szt i = 0; i < getChildCount(); i++)
            {
                auto holder = dynamic_cast<RowHolder *>(getHolder(i));
                auto childSize = InflatableNode::inflate(holder->child, {contentSize.x * holder->hWeight, contentSize.y * holder->vWeight});
                holder->size = childSize;
                length += childSize.x;
            }
            m_length = length;
        }
        return size;
    }

    void RowLayout::onPlace(const sf::Vector2f &position)
    {
        placeBlock(position);
        if (getChildCount() > 0)
        {
            auto contentBox = getContentBox();
            f32t offset = 0;
            auto place = [&](RowHolder *holder)
            {
                auto _contentBox = contentBox;
                _contentBox.setLeft(_contentBox.getLeft() + offset);
                _contentBox.setHeight(holder->size.y, holder->vAnchor);
                InflatableNode::place(holder->child, {_contentBox.getLeft(), _contentBox.getTop()});
                offset += holder->size.x;
            };
            switch (m_direction)
            {
            case Forward:
                contentBox.setWidth(m_length, m_hAnchor);
                for (szt i = 0; i < getChildCount(); i++)
                {
                    auto holder = dynamic_cast<RowHolder *>(getHolder(i));
                    place(holder);
                }
                break;
            case Reverse:
                switch (m_hAnchor)
                {
                case Start:
                    contentBox.setWidth(m_length, End);
                    break;
                case End:
                    contentBox.setWidth(m_length, Start);
                    break;
                case Center:
                    contentBox.setWidth(m_length, Center);
                    break;
                }
                for (szt i = getChildCount(); i > 0; i--)
                {
                    auto holder = dynamic_cast<RowHolder *>(getHolder(i - 1));
                    place(holder);
                }
                break;
            }
        }
    }

    RowLayout::RowHolder::RowHolder(Node &child)
        : Holder(child),
          vAnchor(Start),
          hWeight(0),
          vWeight(1),
          size()
    {
    }

    RowLayout::RowHolder::~RowHolder() = default;

}