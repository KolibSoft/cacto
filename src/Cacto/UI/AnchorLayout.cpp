#include <stdexcept>
#include <Cacto/UI/AnchorLayout.hpp>

namespace cacto
{

    Box::Anchor AnchorLayout::getHorizontalAnchor(const Node &child) const
    {
        auto holder = dynamic_cast<const AnchorHolder *>(getHolder(child));
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child");
        return holder->hAnchor;
    }

    void AnchorLayout::setHorizontalAnchor(Node &child, Anchor value)
    {
        auto holder = dynamic_cast<AnchorHolder *>(getHolder(child));
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child");
        holder->hAnchor = value;
    }

    Box::Anchor AnchorLayout::getVerticalAnchor(const Node &child) const
    {
        auto holder = dynamic_cast<const AnchorHolder *>(getHolder(child));
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child");
        return holder->vAnchor;
    }

    void AnchorLayout::setVerticalAnchor(Node &child, Anchor value)
    {
        auto holder = dynamic_cast<AnchorHolder *>(getHolder(child));
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child");
        holder->vAnchor = value;
    }

    f32t AnchorLayout::getHorizontalWeight(const Node &child) const
    {
        auto holder = dynamic_cast<const AnchorHolder *>(getHolder(child));
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child");
        return holder->hWeight;
    }

    void AnchorLayout::setHorizontalWeight(Node &child, f32t value)
    {
        auto holder = dynamic_cast<AnchorHolder *>(getHolder(child));
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child");
        holder->hWeight = value;
    }

    f32t AnchorLayout::getVerticalWeight(const Node &child) const
    {
        auto holder = dynamic_cast<const AnchorHolder *>(getHolder(child));
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child");
        return holder->vWeight;
    }

    void AnchorLayout::setVerticalWeight(Node &child, f32t value)
    {
        auto holder = dynamic_cast<AnchorHolder *>(getHolder(child));
        if (holder == nullptr)
            throw std::runtime_error("The node is not a child");
        holder->vWeight = value;
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
        auto size = inflateBlock(containerSize);
        if (getChildCount() > 0)
        {
            auto contentBox = getContentBox();
            sf::Vector2f contentSize{contentBox.getWidth(), contentBox.getHeight()};
            for (szt i = 0; i < getChildCount(); i++)
            {
                auto holder = dynamic_cast<AnchorHolder *>(getHolder(i));
                auto childSize = InflatableNode::inflate(holder->child, {contentSize.x * holder->hWeight, contentSize.y * holder->vWeight});
                holder->size = childSize;
            }
        }
        return size;
    }

    void AnchorLayout::onPlace(const sf::Vector2f &position)
    {
        placeBlock(position);
        if (getChildCount() > 0)
        {
            auto contentBox = getContentBox();
            for (szt i = 0; i < getChildCount(); i++)
            {
                auto holder = dynamic_cast<AnchorHolder *>(getHolder(i));
                auto _contentBox = contentBox;
                _contentBox.setWidth(holder->size.x, holder->hAnchor);
                _contentBox.setHeight(holder->size.y, holder->vAnchor);
                InflatableNode::place(holder->child, {_contentBox.getLeft(), _contentBox.getTop()});
            }
        }
    }

    AnchorLayout::AnchorHolder::AnchorHolder(Node &child)
        : Holder(child),
          hAnchor(Start),
          vAnchor(Start),
          hWeight(1),
          vWeight(1),
          size()
    {
    }

    AnchorLayout::AnchorHolder::~AnchorHolder() {}

}