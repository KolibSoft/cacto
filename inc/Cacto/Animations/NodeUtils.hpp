#pragma once

#include <Cacto/Animations/Export.hpp>

namespace sf
{
    class Time;
}

namespace cacto
{

    class Node;

    void CACTO_ANIMATIONS_API update(Node &node, const sf::Time &time);
    void CACTO_ANIMATIONS_API updateChildren(const Node &node, const sf::Time &time);

}