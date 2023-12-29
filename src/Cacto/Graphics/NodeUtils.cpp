#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/Core/Node.hpp>
#include <Cacto/Graphics/NodeUtils.hpp>

namespace cacto
{

    void draw(const Node &node, sf::RenderTarget &target, const sf::RenderStates &states)
    {
        auto drawable = dynamic_cast<const sf::Drawable *>(&node);
        if (drawable)
            target.draw(*drawable, states);
        else
            drawChildren(node, target, states);
    }

    void drawChildren(const Node &node, sf::RenderTarget &target, const sf::RenderStates &states)
    {
        auto childCount = node.getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = node.getChild(i);
            if (child)
                draw(*child, target, states);
        }
    }

}