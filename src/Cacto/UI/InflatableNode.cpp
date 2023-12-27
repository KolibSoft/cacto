#include <math.h>
#include <Cacto/UI/InflatableNode.hpp>

namespace cacto
{

    sf::Vector2f InflatableNode::compact()
    {
        auto size = compactChildren();
        return size;
    }

    sf::Vector2f InflatableNode::compactChildren() const
    {
        sf::Vector2f size{0, 0};
        auto childCount = getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = getChild(i);
            if (child)
            {
                auto childSize = InflatableNode::compact(*child);
                size.x = std::max(size.x, childSize.x);
                size.y = std::max(size.y, childSize.y);
            }
        }
        return size;
    }

    sf::Vector2f InflatableNode::inflate(const sf::Vector2f &containerSize)
    {
        auto size = inflateChildren(containerSize);
        return size;
    }

    sf::Vector2f InflatableNode::inflateChildren(const sf::Vector2f &containerSize) const
    {
        sf::Vector2f size{0, 0};
        auto childCount = getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = getChild(i);
            if (child)
            {
                auto childSize = InflatableNode::inflate(*child, containerSize);
                size.x = std::max(size.x, childSize.x);
                size.y = std::max(size.y, childSize.y);
            }
        }
        return size;
    }

    void InflatableNode::place(const sf::Vector2f &position)
    {
        placeChildren(position);
    }

    void InflatableNode::placeChildren(const sf::Vector2f &position)
    {
        auto childCount = getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = getChild(i);
            if (child)
                InflatableNode::place(*child, position);
        }
    }

    InflatableNode::InflatableNode() = default;

    InflatableNode::~InflatableNode() = default;

    sf::Vector2f InflatableNode::compact(Node &node)
    {
        auto inflatableNode = dynamic_cast<InflatableNode *>(&node);
        if (inflatableNode)
        {
            auto size = inflatableNode->compact();
            return size;
        }
        else
        {
            auto size = InflatableNode::compactChildren(node);
            return size;
        }
    }

    sf::Vector2f InflatableNode::compactChildren(const Node &node)
    {
        sf::Vector2f size{0, 0};
        auto childCount = node.getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = node.getChild(i);
            if (child)
            {
                auto childSize = InflatableNode::compact(*child);
                size.x = std::max(size.x, childSize.x);
                size.y = std::max(size.y, childSize.y);
            }
        }
        return size;
    }

    sf::Vector2f InflatableNode::inflate(Node &node, const sf::Vector2f &containerSize)
    {
        auto inflatableNode = dynamic_cast<InflatableNode *>(&node);
        if (inflatableNode)
        {
            auto size = inflatableNode->inflate(containerSize);
            return size;
        }
        else
        {
            auto size = InflatableNode::inflateChildren(node, containerSize);
            return size;
        }
    }

    sf::Vector2f InflatableNode::inflateChildren(const Node &node, const sf::Vector2f &containerSize)
    {
        sf::Vector2f size{0, 0};
        auto childCount = node.getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = node.getChild(i);
            if (child)
            {
                auto childSize = InflatableNode::inflate(*child, containerSize);
                size.x = std::max(size.x, childSize.x);
                size.y = std::max(size.y, childSize.y);
            }
        }
        return size;
    }

    void InflatableNode::place(Node &node, const sf::Vector2f &position)
    {
        auto inflatableNode = dynamic_cast<InflatableNode *>(&node);
        if (inflatableNode)
            inflatableNode->place(position);
        else
            InflatableNode::placeChildren(node, position);
    }

    void InflatableNode::placeChildren(const Node &node, const sf::Vector2f &position)
    {
        auto childCount = node.getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = node.getChild(i);
            if (child)
                InflatableNode::place(*child, position);
        }
    }

}