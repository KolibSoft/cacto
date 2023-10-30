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

    sf::Vector2f RowLayout::onCompact(const sf::Vector2f &contentSize)
    {
        sf::Vector2f _contentSize{contentSize};
        if (getChildCount() > 0)
        {
            f32t length = 0;
            for (szt i = 0; i < getChildCount(); i++)
            {
                auto holder = getHolder(i);
                auto size = InflatableNode::compact(holder->child, contentSize);
                length += size.x;
                _contentSize.y = std::max(size.y, _contentSize.y);
            }
            m_length = length;
            _contentSize.x = std::max(length, _contentSize.x);
        }
        auto boxSize = Block::onCompact(_contentSize);
        return boxSize;
    }

    sf::Vector2f RowLayout::onInflate(const sf::Vector2f &containerSize)
    {
        auto boxSize = Block::onInflate(containerSize);
        if (getChildCount() > 0)
        {
            auto contentBox = getContentBox();
            sf::Vector2f _containerSize{0, contentBox.getHeight()};
            for (szt i = 0; i < getChildCount(); i++)
            {
                auto holder = dynamic_cast<RowHolder *>(getHolder(i));
                auto _boxSize = InflatableNode::inflate(holder->child, _containerSize);
                holder->boxSize = _boxSize;
            }
        }
        return boxSize;
    }

    void RowLayout::onPlace(const sf::Vector2f &position)
    {
        Block::onPlace(position);
        if (getChildCount() > 0)
        {
            auto contentBox = getContentBox();
            sf::Vector2f containerSize{contentBox.getWidth(), contentBox.getHeight()};
            sf::Vector2f contentPosition{contentBox.getLeft(), contentBox.getTop()};
            f32t offset = 0;
            switch (m_hAnchor)
            {
            case Start:
                break;
            case End:
                offset += containerSize.x - m_length;
                break;
            case Center:
                offset += (containerSize.x - m_length) / 2;
                break;
            }
            auto place = [&](RowHolder *holder)
            {
                auto &boxSize = holder->boxSize;
                auto _contentPosition{contentPosition};
                _contentPosition.x += offset;
                switch (holder->vAnchor)
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
                InflatableNode::place(holder->child, _contentPosition);
                offset += holder->boxSize.x;
            };
            switch (m_direction)
            {
            case Forward:
                for (szt i = 0; i < getChildCount(); i++)
                {
                    auto holder = dynamic_cast<RowHolder *>(getHolder(i));
                    place(holder);
                }
                break;
            case Reverse:
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
          boxSize()
    {
    }

    RowLayout::RowHolder::~RowHolder() = default;

}