#pragma once

#include <SFML/Graphics/RenderStates.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class RenderTarget;
}

namespace cacto
{

    class Node;

    void CACTO_GRAPHICS_API draw(const Node &node, sf::RenderTarget &target, const sf::RenderStates &states = sf::RenderStates::Default);
    void CACTO_GRAPHICS_API drawChildren(const Node &node, sf::RenderTarget &target, const sf::RenderStates &states = sf::RenderStates::Default);

}