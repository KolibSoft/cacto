#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <Cacto/Config.hpp>

namespace sf
{
    class Event;
}

namespace cacto
{

    class Clickable
    {
    public:
        virtual void click(sf::Mouse::Button button = sf::Mouse::Left, const sf::Vector2f &position = {0, 0}) = 0;

        Clickable() = default;
        virtual ~Clickable() = default;
    };

}
