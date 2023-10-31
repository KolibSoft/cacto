#include <stdexcept>
#include <Cacto/UI/FrameLayout.hpp>

namespace cacto
{

    Box::Anchor FrameLayout::getHorizontalAnchor(const Node &child) const
    {
        auto holder = dynamic_cast<const FrameHolder *>(getHolder(child));
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child");
        return holder->hAnchor;
    }

    void FrameLayout::setHorizontalAnchor(Node &child, Anchor value)
    {
        auto holder = dynamic_cast<FrameHolder *>(getHolder(child));
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child");
        holder->hAnchor = value;
    }

    Box::Anchor FrameLayout::getVerticalAnchor(const Node &child) const
    {
        auto holder = dynamic_cast<const FrameHolder *>(getHolder(child));
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child");
        return holder->vAnchor;
    }

    void FrameLayout::setVerticalAnchor(Node &child, Anchor value)
    {
        auto holder = dynamic_cast<FrameHolder *>(getHolder(child));
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child");
        holder->vAnchor = value;
    }

    FrameLayout::FrameLayout() = default;
    FrameLayout::~FrameLayout() = default;

    FrameLayout::FrameLayout(const FrameLayout &other) = default;
    FrameLayout &FrameLayout::operator=(const FrameLayout &other) = default;

    FrameLayout::Holder *FrameLayout::onHold(Node &child) const
    {
        auto holder = new FrameHolder(child);
        return holder;
    }

    void FrameLayout::onAppend(Node &child)
    {
        if (getChild() != nullptr)
            throw std::runtime_error("This node can not has more child nodes");
        Layout::onAppend(child);
    }

    void FrameLayout::onRemove(Node &child)
    {
        if (getChild() != &child)
            throw std::runtime_error("The node is not a child node");
        Layout::onRemove(child);
    }

    sf::Vector2f FrameLayout::onCompact(const sf::Vector2f &contentSize)
    {
        auto _contentSize = contentSize;
        auto holder = dynamic_cast<FrameHolder *>(getHolder());
        if (holder)
        {
            auto size = InflatableNode::compact(holder->child, contentSize);
            _contentSize.x = std::max(size.x, _contentSize.x);
            _contentSize.y = std::max(size.y, _contentSize.y);
        }
        auto outerSize = Block::onCompact(_contentSize);
        return outerSize;
    }

    sf::Vector2f FrameLayout::onInflate(const sf::Vector2f &containerSize)
    {
        auto outerSize = Block::onInflate(containerSize);
        auto holder = dynamic_cast<FrameHolder *>(getHolder());
        if (holder)
        {
            auto contentBox = getContentBox();
            sf::Vector2f _containerSize{contentBox.getWidth(), contentBox.getHeight()};
            auto _boxSize = InflatableNode::inflate(holder->child, _containerSize);
            holder->boxSize = _boxSize;
        }
        return outerSize;
    }

    void FrameLayout::onPlace(const sf::Vector2f &position)
    {
        Block::onPlace(position);
        auto holder = dynamic_cast<FrameHolder *>(getHolder());
        if (holder)
        {
            auto contentBox = getContentBox();
            sf::Vector2f containerSize{contentBox.getWidth(), contentBox.getHeight()};
            sf::Vector2f contentPosition{contentBox.getLeft(), contentBox.getTop()};
            auto &boxSize = holder->boxSize;
            switch (holder->hAnchor)
            {
            case Start:
                break;
            case End:
                contentPosition.x += containerSize.x - boxSize.x;
                break;
            case Center:
                contentPosition.x += (containerSize.x - boxSize.x) / 2;
                break;
            }
            switch (holder->vAnchor)
            {
            case Start:
                break;
            case End:
                contentPosition.y += containerSize.y - boxSize.y;
                break;
            case Center:
                contentPosition.y += (containerSize.y - boxSize.y) / 2;
                break;
            }
            InflatableNode::place(holder->child, contentPosition);
        }
    }

    FrameLayout::FrameHolder::FrameHolder(Node &child)
        : Holder(child),
          hAnchor(Start),
          vAnchor(Start),
          boxSize()
    {
    }

    FrameLayout::FrameHolder::~FrameHolder() = default;

}