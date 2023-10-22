#include <stdexcept>
#include <algorithm>
#include <Cacto/UI/RowLayout.hpp>

namespace cacto
{

    RowLayout::RowLayout() = default;
    RowLayout::~RowLayout() = default;

    RowLayout::RowLayout(const RowLayout &other) = default;
    RowLayout &RowLayout::operator=(const RowLayout &other) = default;

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
            auto padding = getPadding();
            Box box{*this};
            box.shrink(padding);
            sf::Vector2f _containerSize{0, box.getHeight()};
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
            auto padding = getPadding();
            Box box{*this};
            box.shrink(padding);
            sf::Vector2f contentPosition{box.getLeft(), box.getTop()};
            f32t offset = 0;
            for (szt i = 0; i < getChildCount(); i++)
            {
                auto _contentPosition{contentPosition};
                _contentPosition.x += offset;
                auto holder = dynamic_cast<RowHolder *>(getHolder(i));
                InflatableNode::place(holder->child, _contentPosition);
                offset += holder->boxSize.x;
            }
        }
    }

    RowLayout::RowHolder::RowHolder(Node &child)
        : Holder(child),
          boxSize()
    {
    }

    RowLayout::RowHolder::~RowHolder() = default;

}