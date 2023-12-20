#include <Cacto/Graphics/DrawNode.hpp>

namespace cacto
{

    void DrawNode::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        auto object = dynamic_cast<const Object *>(this);
        if (object)
            DrawNode::draw(object->as<Node>(), target, states);
    }

    DrawNode::DrawNode() = default;

    DrawNode::~DrawNode() = default;

    void DrawNode::draw(const Shared<const Node> &node, sf::RenderTarget &target, const sf::RenderStates &states)
    {
        if (node == nullptr)
            throw std::runtime_error("The node was null");
        auto drawNode = std::dynamic_pointer_cast<const DrawNode>(node);
        if (drawNode)
            drawNode->onDraw(target, states);
        else
            DrawNode::drawChildren(node, target, states);
    }

    void DrawNode::drawChildren(const Shared<const Node> &node, sf::RenderTarget &target, const sf::RenderStates &states)
    {
        if (node == nullptr)
            throw std::runtime_error("The node was null");
        auto childCount = node->getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = node->getChild(i);
            if (child)
                DrawNode::draw(child, target, states);
        }
    }

    void DrawNode::drawChildren(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        auto object = dynamic_cast<const Object *>(this);
        if (object)
            DrawNode::drawChildren(object->as<Node>(), target, states);
    }

    void DrawNode::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        drawChildren(target, states);
    }

}