#pragma once

#include <SFML/System/Vector2.hpp>
#include <Cacto/UI/Export.hpp>

namespace cacto
{

    class Node;

    sf::Vector2f CACTO_UI_API compact(Node &node);
    sf::Vector2f CACTO_UI_API compactChildren(const Node &node);

    sf::Vector2f CACTO_UI_API inflate(Node &node, const sf::Vector2f &containerSize = {0, 0});
    sf::Vector2f CACTO_UI_API inflateChildren(const Node &node, const sf::Vector2f &containerSize = {0, 0});

    void CACTO_UI_API place(Node &node, const sf::Vector2f &position = {0, 0});
    void CACTO_UI_API placeChildren(const Node &node, const sf::Vector2f &position = {0, 0});

}