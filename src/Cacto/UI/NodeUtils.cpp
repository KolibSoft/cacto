#include <Cacto/Core/Node.hpp>
#include <Cacto/UI/Inflatable.hpp>
#include <Cacto/UI/NodeUtils.hpp>

namespace cacto
{

    sf::Vector2f compact(Node &node)
    {
        auto inflatableNode = dynamic_cast<Inflatable *>(&node);
        if (inflatableNode)
        {
            auto size = inflatableNode->compact();
            return size;
        }
        else
        {
            auto size = compactChildren(node);
            return size;
        }
    }

    sf::Vector2f compactChildren(const Node &node)
    {
        sf::Vector2f size{0, 0};
        auto childCount = node.getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = node.getChild(i);
            if (child)
            {
                auto childSize = compact(*child);
                size.x = std::max(size.x, childSize.x);
                size.y = std::max(size.y, childSize.y);
            }
        }
        return size;
    }

    sf::Vector2f inflate(Node &node, const sf::Vector2f &containerSize)
    {
        auto inflatableNode = dynamic_cast<Inflatable *>(&node);
        if (inflatableNode)
        {
            auto size = inflatableNode->inflate(containerSize);
            return size;
        }
        else
        {
            auto size = inflateChildren(node, containerSize);
            return size;
        }
    }

    sf::Vector2f inflateChildren(const Node &node, const sf::Vector2f &containerSize)
    {
        sf::Vector2f size{0, 0};
        auto childCount = node.getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = node.getChild(i);
            if (child)
            {
                auto childSize = inflate(*child, containerSize);
                size.x = std::max(size.x, childSize.x);
                size.y = std::max(size.y, childSize.y);
            }
        }
        return size;
    }

    void place(Node &node, const sf::Vector2f &position)
    {
        auto inflatableNode = dynamic_cast<Inflatable *>(&node);
        if (inflatableNode)
            inflatableNode->place(position);
        else
            placeChildren(node, position);
    }

    void placeChildren(const Node &node, const sf::Vector2f &position)
    {
        auto childCount = node.getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = node.getChild(i);
            if (child)
                place(*child, position);
        }
    }

}