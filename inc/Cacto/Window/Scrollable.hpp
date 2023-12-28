#pragma once

#include <SFML/Window/Mouse.hpp>
#include <Cacto/Config.hpp>

namespace sf
{
    class Event;
}

namespace cacto
{

    class CACTO_WINDOW_API Scrollable
    {

    public:
        virtual void scroll(sf::Mouse::Wheel wheel = sf::Mouse::Wheel::VerticalWheel, f32t delta = 0, i32t x = 0, i32t y = 0) = 0;

        Scrollable() = default;
        virtual ~Scrollable() = default;
    };

}
