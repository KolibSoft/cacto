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

    sf::Vector2f ColumnLayout::onCompact(const sf::Vector2f &contentSize)
    {
        sf::Vector2f _contentSize{contentSize};
        if (getChildCount() > 0)
        {
            f32t length = 0;
            for (szt i = 0; i < getChildCount(); i++)
            {
                auto holder = getHolder(i);
                auto size = InflatableNode::compact(holder->child, contentSize);
                length += size.y;
                _contentSize.x = std::max(size.x, _contentSize.x);
            }
            m_length = length;
            _contentSize.y = std::max(length, _contentSize.y);
        }
        auto boxSize = Block::onCompact(_contentSize);
        return boxSize;
    }

    sf::Vector2f ColumnLayout::onInflate(const sf::Vector2f &containerSize)
    {
        auto boxSize = Block::onInflate(containerSize);
        if (getChildCount() > 0)
        {
            f32t length = 0;
            auto contentBox = getContentBox();
            sf::Vector2f _containerSize{contentBox.getWidth(), contentBox.getHeight()};
            for (szt i = 0; i < getChildCount(); i++)
            {
                auto holder = dynamic_cast<ColumnHolder *>(getHolder(i));
                auto size = InflatableNode::inflate(holder->child, {_containerSize.x * holder->hWeight, _containerSize.y * holder->vWeight});
                holder->boxSize = size;
                length += size.y;
            }
            m_length = length;
        }
        return boxSize;
    }

    void ColumnLayout::onPlace(const sf::Vector2f &position)
    {
        Block::onPlace(position);
        if (getChildCount() > 0)
        {
            auto contentBox = getContentBox();
            sf::Vector2f containerSize{contentBox.getWidth(), contentBox.getHeight()};
            sf::Vector2f contentPosition{contentBox.getLeft(), contentBox.getTop()};
            f32t offset = 0;
            auto place = [&](ColumnHolder *holder)
            {
                auto &boxSize = holder->boxSize;
                auto _contentPosition{contentPosition};
                _contentPosition.y += offset;
                switch (holder->hAnchor)
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
                InflatableNode::place(holder->child, _contentPosition);
                offset += holder->boxSize.y;
            };
            switch (m_direction)
            {
            case Forward:
                switch (m_vAnchor)
                {
                case Start:
                    break;
                case End:
                    offset += containerSize.y - m_length;
                    break;
                case Center:
                    offset += (containerSize.y - m_length) / 2;
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
                    offset += containerSize.y - m_length;
                    break;
                case End:
                    break;
                case Center:
                    offset += (containerSize.y - m_length) / 2;
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
          boxSize()
    {
    }

    ColumnLayout::ColumnHolder::~ColumnHolder() = default;

}