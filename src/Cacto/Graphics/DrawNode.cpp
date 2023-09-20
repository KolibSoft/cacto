#include <Cacto/Graphics/DrawNode.hpp>

namespace cacto
{

    void DrawNode::draw(sf::RenderTarget &target, const sf::RenderStates &states)
    {
        onDraw(target, states);
    }

    DrawNode::DrawNode() = default;

    DrawNode::~DrawNode() = default;

    void DrawNode::draw(Node &node, sf::RenderTarget &target, const sf::RenderStates &states)
    {
        auto drawNode = dynamic_cast<DrawNode *>(&node);
        auto handled = drawNode && drawNode->onDraw(target, states);
        if (!handled)
        {
            auto childCount = node.getChildCount();
            for (szt i = 0; i < childCount; i++)
            {
                auto child = node.getChild(i);
                DrawNode::draw(*child, target, states);
            }
        }
    }

    bool DrawNode::onDraw(sf::RenderTarget &target, const sf::RenderStates &states)
    {
        return false;
    }

}