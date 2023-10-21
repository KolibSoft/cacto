#include <stdexcept>
#include <Cacto/UI/AnchorLayout.hpp>

namespace cacto
{

    Box::Anchor AnchorLayout::getHorizontalAnchor(const Node &child) const
    {
        auto holder = getHolder(child);
        if (!holder)
            throw std::runtime_error("The node is not a child");
        auto _holder = dynamic_cast<const AnchorHolder *>(holder);
        return _holder->hAnchor;
    }

    void AnchorLayout::setHorizontalAnchor(Node &child, Anchor value)
    {
        auto holder = getHolder(child);
        if (!holder)
            throw std::runtime_error("The node is not a child");
        auto _holder = dynamic_cast<AnchorHolder *>(holder);
        _holder->hAnchor = value;
    }

    Box::Anchor AnchorLayout::getVerticalAnchor(const Node &child) const
    {
        auto holder = getHolder(child);
        if (!holder)
            throw std::runtime_error("The node is not a child");
        auto _holder = dynamic_cast<const AnchorHolder *>(holder);
        return _holder->vAnchor;
    }

    void AnchorLayout::setVerticalAnchor(Node &child, Anchor value)
    {
        auto holder = getHolder(child);
        if (!holder)
            throw std::runtime_error("The node is not a child");
        auto _holder = dynamic_cast<AnchorHolder *>(holder);
        _holder->vAnchor = value;
    }

    AnchorLayout::AnchorLayout() = default;
    AnchorLayout::~AnchorLayout() = default;

    AnchorLayout::AnchorLayout(const AnchorLayout &other) = default;
    AnchorLayout &AnchorLayout::operator=(const AnchorLayout &other) = default;

    AnchorLayout::AnchorHolder *AnchorLayout::onHold(Node &child) const
    {
        auto holder = new AnchorHolder(child);
        return holder;
    }

    sf::Vector2f AnchorLayout::onInflate(const sf::Vector2f &containerSize)
    {
        auto boxSize = Block::onInflate(containerSize);
        if (getChildCount() > 0)
        {
            auto padding = getPadding();
            Box box{*this};
            box.shrink(padding);
            sf::Vector2f _containerSize{box.getWidth(), box.getHeight()};
            for (szt i = 0; i < getChildCount(); i++)
            {
                auto holder = getHolder(i);
                auto _holder = dynamic_cast<AnchorHolder *>(holder);
                auto _boxSize = InflatableNode::inflate(_holder->child, _containerSize);
                _holder->boxSize = _boxSize;
            }
        }
        return boxSize;
    }

    void AnchorLayout::onPlace(const sf::Vector2f &position)
    {
        Block::onPlace(position);
        if (getChildCount() > 0)
        {
            auto padding = getPadding();
            Box box{*this};
            box.shrink(padding);
            sf::Vector2f contentPosition{box.getLeft(), box.getTop()};
            sf::Vector2f containerSize{box.getWidth(), box.getHeight()};
            for (szt i = 0; i < getChildCount(); i++)
            {
                auto holder = getHolder(i);
                auto _holder = dynamic_cast<AnchorHolder *>(holder);
                auto &boxSize = _holder->boxSize;
                auto _contentPosition = contentPosition;
                switch (_holder->hAnchor)
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
                switch (_holder->vAnchor)
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
                InflatableNode::place(_holder->child, _contentPosition);
            }
        }
    }

    AnchorLayout::AnchorHolder::AnchorHolder(Node &child)
        : Holder(child),
          hAnchor(Start),
          vAnchor(Start),
          boxSize()
    {
    }

    AnchorLayout::AnchorHolder::~AnchorHolder() {}

}