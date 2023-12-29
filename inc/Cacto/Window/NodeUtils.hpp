#pragma once

#include <Cacto/Window/Export.hpp>

namespace sf
{
    class Event;
}

namespace cacto
{

    class Node;

    bool CACTO_WINDOW_API handle(Node &node, const sf::Event &event);
    bool CACTO_WINDOW_API handleChildren(const Node &node, const sf::Event &event);

    bool CACTO_WINDOW_API bubble(Node &node, Node &target, const sf::Event &event);
    bool CACTO_WINDOW_API bubbleParent(const Node &node, Node &target, const sf::Event &event);

}