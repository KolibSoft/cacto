#include <math.h>
#include <Cacto/UI/InflatableNode.hpp>

namespace cacto
{

    sf::Vector2f InflatableNode::compact()
    {
        auto object = dynamic_cast<Object *>(this);
        if (object)
        {
            auto size = InflatableNode::compact(object->as<Node>());
            return size;
        }
        return {};
    }

    sf::Vector2f InflatableNode::inflate(const sf::Vector2f &containerSize)
    {
        auto object = dynamic_cast<Object *>(this);
        if (object)
        {
            auto size = InflatableNode::inflate(object->as<Node>(), containerSize);
            return size;
        }
        return {};
    }

    void InflatableNode::place(const sf::Vector2f &position)
    {
        auto object = dynamic_cast<Object *>(this);
        if (object)
            InflatableNode::place(object->as<Node>(), position);
    }

    InflatableNode::InflatableNode() = default;

    InflatableNode::~InflatableNode() = default;

    sf::Vector2f InflatableNode::compact(const Shared<Node> &node)
    {
        if (node == nullptr)
            throw std::runtime_error("The node was null");
        auto inflatableNode = std::dynamic_pointer_cast<InflatableNode>(node);
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

    sf::Vector2f InflatableNode::compactChildren(const Shared<const Node> &node)
    {
        if (node == nullptr)
            throw std::runtime_error("The node was null");
        sf::Vector2f size{0, 0};
        auto childCount = node->getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = node->getChild(i);
            if (child)
            {
                auto childSize = InflatableNode::compact(child);
                size.x = std::max(size.x, childSize.x);
                size.y = std::max(size.y, childSize.y);
            }
        }
        return size;
    }

    sf::Vector2f InflatableNode::inflate(const Shared<Node> &node, const sf::Vector2f &containerSize)
    {
        if (node == nullptr)
            throw std::runtime_error("The node was null");
        auto inflatableNode = std::dynamic_pointer_cast<InflatableNode>(node);
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

    sf::Vector2f InflatableNode::inflateChildren(const Shared<const Node> &node, const sf::Vector2f &containerSize)
    {
        if (node == nullptr)
            throw std::runtime_error("The node was null");
        sf::Vector2f size{0, 0};
        auto childCount = node->getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = node->getChild(i);
            if (child)
            {
                auto childSize = InflatableNode::inflate(child, containerSize);
                size.x = std::max(size.x, childSize.x);
                size.y = std::max(size.y, childSize.y);
            }
        }
        return size;
    }

    void InflatableNode::place(const Shared<Node> &node, const sf::Vector2f &position)
    {
        if (node == nullptr)
            throw std::runtime_error("The node was null");
        auto inflatableNode = std::dynamic_pointer_cast<InflatableNode>(node);
        if (inflatableNode)
            inflatableNode->onPlace(position);
        else
            InflatableNode::placeChildren(node, position);
    }

    void InflatableNode::placeChildren(const Shared<const Node> &node, const sf::Vector2f &position)
    {
        if (node == nullptr)
            throw std::runtime_error("The node was null");
        auto childCount = node->getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = node->getChild(i);
            if (child)
                InflatableNode::place(child, position);
        }
    }

    sf::Vector2f InflatableNode::compactChildren() const
    {
        auto object = dynamic_cast<const Object *>(this);
        if (object)
        {
            auto size = InflatableNode::compactChildren(object->as<Node>());
            return size;
        }
        return {};
    }

    sf::Vector2f InflatableNode::inflateChildren(const sf::Vector2f &containerSize) const
    {
        auto object = dynamic_cast<const Object *>(this);
        if (object)
        {
            auto size = InflatableNode::inflateChildren(object->as<Node>(), containerSize);
            return size;
        }
        return {};
    }

    void InflatableNode::placeChildren(const sf::Vector2f &position)
    {
        auto object = dynamic_cast<const Object *>(this);
        if (object)
            InflatableNode::placeChildren(object->as<Node>(), position);
    }

    sf::Vector2f InflatableNode::onCompact()
    {
        auto size = compactChildren();
        return size;
    }

    sf::Vector2f InflatableNode::onInflate(const sf::Vector2f &containerSize)
    {
        auto size = inflateChildren(containerSize);
        return size;
    }

    void InflatableNode::onPlace(const sf::Vector2f &position)
    {
        placeChildren(position);
    }

}