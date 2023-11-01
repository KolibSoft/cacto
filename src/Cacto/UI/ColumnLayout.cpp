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
        auto size = compactBlock(contentSize);
        return size;
    }

    sf::Vector2f ColumnLayout::onInflate(const sf::Vector2f &containerSize)
    {
        auto size = inflateBlock(containerSize);
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
        placeBlock(position);
        if (getChildCount() > 0)
        {
            auto contentBox = getContentBox();
            f32t offset = 0;
            auto place = [&](ColumnHolder *holder)
            {
                auto _contentBox = contentBox;
                _contentBox.setTop(_contentBox.getTop() + offset);
                _contentBox.setWidth(holder->size.x, holder->hAnchor);
                InflatableNode::place(holder->child, {_contentBox.getLeft(), _contentBox.getTop()});
                offset += holder->size.y;
            };
            switch (m_direction)
            {
            case Forward:
                contentBox.setHeight(m_length, m_vAnchor);
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
                    contentBox.setHeight(m_length, End);
                    break;
                case End:
                    contentBox.setHeight(m_length, Start);
                    break;
                case Center:
                    contentBox.setHeight(m_length, Center);
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