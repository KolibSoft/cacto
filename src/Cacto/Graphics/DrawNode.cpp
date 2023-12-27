#include <Cacto/Graphics/DrawNode.hpp>

namespace cacto
{

    void DrawNode::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        drawChildren(target, states);
    }

    void DrawNode::drawChildren(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        DrawNode::drawChildren(*this, target, states);
    }

    DrawNode::DrawNode() = default;

    DrawNode::~DrawNode() = default;

    void DrawNode::draw(const Node &node, sf::RenderTarget &target, const sf::RenderStates &states)
    {
        auto drawNode = dynamic_cast<const DrawNode *>(&node);
        if (drawNode)
            drawNode->draw(target, states);
        else
            DrawNode::drawChildren(node, target, states);
    }

    void DrawNode::drawChildren(const Node &node, sf::RenderTarget &target, const sf::RenderStates &states)
    {
        auto childCount = node.getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = node.getChild(i);
            if (child)
                DrawNode::draw(*child, target, states);
        }
    }

}