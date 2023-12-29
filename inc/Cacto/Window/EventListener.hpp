#pragma once

#include <functional>

namespace sf
{
    class Event;
}

namespace cacto
{

    class Node;

    using EventListener = std::function<void(Node &target, const sf::Event &event)>;

}