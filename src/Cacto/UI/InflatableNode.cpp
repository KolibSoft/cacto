#include <math.h>
#include <Cacto/UI/InflatableNode.hpp>

namespace cacto
{

    sf::Vector2f InflatableNode::compact()
    {
        auto size = InflatableNode::compact(*this);
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

    sf::Vector2f InflatableNode::compact(Node &node)
    {
        auto inflatableNode = dynamic_cast<InflatableNode *>(&node);
        if (inflatableNode)
        {
            auto size = inflatableNode->onCompact();
            return size;
        }
        else
        {
            auto size = InflatableNode::compactChildren(node);
            return size;
        }
    }

    sf::Vector2f InflatableNode::compactChildren(Node &node)
    {
        sf::Vector2f size{0, 0};
        auto childCount = node.getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = node.getChild(i);
            auto childSize = InflatableNode::compact(*child);
            size.x = std::max(size.x, childSize.x);
            size.y = std::max(size.y, childSize.y);
        }
        return size;
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
            auto size = InflatableNode::inflateChildren(node, containerSize);
            return size;
        }
    }

    sf::Vector2f InflatableNode::inflateChildren(Node &node, const sf::Vector2f &containerSize)
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

    void InflatableNode::place(Node &node, const sf::Vector2f &position)
    {
        auto inflatableNode = dynamic_cast<InflatableNode *>(&node);
        if (inflatableNode)
            inflatableNode->onPlace(position);
        else
            InflatableNode::placeChildren(node, position);
    }

    void InflatableNode::placeChildren(Node &node, const sf::Vector2f &position)
    {
        auto childCount = node.getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = node.getChild(i);
            InflatableNode::place(*child, position);
        }
    }

    sf::Vector2f InflatableNode::onCompact()
    {
        auto size = InflatableNode::compactChildren(*this);
        return size;
    }

    sf::Vector2f InflatableNode::onInflate(const sf::Vector2f &containerSize)
    {
        auto size = InflatableNode::inflateChildren(*this, containerSize);
        return size;
    }

    void InflatableNode::onPlace(const sf::Vector2f &position)
    {
        InflatableNode::placeChildren(*this, position);
    }

}