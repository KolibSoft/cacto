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

    sf::Vector2f FrameLayout::onInflate(const sf::Vector2f &containerSize)
    {
        auto size = Block::onInflate(containerSize);
        auto holder = dynamic_cast<FrameHolder *>(getHolder());
        if (holder)
        {
            auto contentBox = getContentBox();
            sf::Vector2f contentSize{contentBox.getWidth(), contentBox.getHeight()};
            auto childSize = InflatableNode::inflate(holder->child, contentSize);
            holder->size = childSize;
        }
        return size;
    }

    void FrameLayout::onPlace(const sf::Vector2f &position)
    {
        Block::onPlace(position);
        auto holder = dynamic_cast<FrameHolder *>(getHolder());
        if (holder)
        {
            auto contentBox = getContentBox();
            sf::Vector2f contentSize{contentBox.getWidth(), contentBox.getHeight()};
            sf::Vector2f contentPosition{contentBox.getLeft(), contentBox.getTop()};
            auto &childSize = holder->size;
            switch (holder->hAnchor)
            {
            case Start:
                break;
            case End:
                contentPosition.x += contentSize.x - childSize.x;
                break;
            case Center:
                contentPosition.x += (contentSize.x - childSize.x) / 2;
                break;
            }
            switch (holder->vAnchor)
            {
            case Start:
                break;
            case End:
                contentPosition.y += contentSize.y - childSize.y;
                break;
            case Center:
                contentPosition.y += (contentSize.y - childSize.y) / 2;
                break;
            }
            InflatableNode::place(holder->child, contentPosition);
        }
    }

    FrameLayout::FrameHolder::FrameHolder(Node &child)
        : Holder(child),
          hAnchor(Start),
          vAnchor(Start),
          size()
    {
    }

    FrameLayout::FrameHolder::~FrameHolder() = default;

}