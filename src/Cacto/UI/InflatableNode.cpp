#include <Cacto/UI/InflatableNode.hpp>

namespace cacto
{

    sf::Vector2f InflatableNode::compact(const sf::Vector2f &contentSize)
    {
        auto size = InflatableNode::compact(*this, contentSize);
        return size;
    }

    sf::Vector2f InflatableNode::inflate(const sf::Vector2f &containerSize)
    {
        auto size = InflatableNode::inflate(*this, containerSize);
        return size;
    }

    void InflatableNode::place(const sf::Vector2f &position)
    {
        InflatableNode::place(*this, position);
    }

    InflatableNode::InflatableNode() = default;

    InflatableNode::~InflatableNode() = default;

    sf::Vector2f InflatableNode::compact(Node &node, const sf::Vector2f &contentSize)
    {
        auto inflatableNode = dynamic_cast<InflatableNode *>(&node);
        if (inflatableNode)
        {
            auto size = inflatableNode->onCompact(contentSize);
            return size;
        }
        else
        {
            sf::Vector2f size{0, 0};
            auto childCount = node.getChildCount();
            for (szt i = 0; i < childCount; i++)
            {
                auto child = node.getChild(i);
                auto childSize = InflatableNode::compact(*child, contentSize);
                size.x = std::max(size.x, childSize.x);
                size.y = std::max(size.y, childSize.y);
            }
            return size;
        }
    }

    sf::Vector2f InflatableNode::inflate(Node &node, const sf::Vector2f &containerSize)
    {
        auto inflatableNode = dynamic_cast<InflatableNode *>(&node);
        if (inflatableNode)
        {
            auto size = inflatableNode->onInflate(containerSize);
            return size;
        }
        else
        {
            sf::Vector2f size{0, 0};
            auto childCount = node.getChildCount();
            for (szt i = 0; i < childCount; i++)
            {
                auto child = node.getChild(i);
                auto childSize = InflatableNode::inflate(*child, containerSize);
                size.x = std::max(size.x, childSize.x);
                size.y = std::max(size.y, childSize.y);
            }
            return size;
        }
    }

    void InflatableNode::place(Node &node, const sf::Vector2f &position)
    {
        auto inflatableNode = dynamic_cast<InflatableNode *>(&node);
        if (inflatableNode)
        {
            inflatableNode->onPlace(position);
        }
        else
        {
            auto childCount = node.getChildCount();
            for (szt i = 0; i < childCount; i++)
            {
                auto child = node.getChild(i);
                InflatableNode::place(*child, position);
            }
        }
    }

}