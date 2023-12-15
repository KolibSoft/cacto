#pragma once

#include <SFML/Window/Mouse.hpp>
#include <Cacto/Window/Export.hpp>

namespace sf
{
    class Event;
}

namespace cacto
{

    class CACTO_WINDOW_API Scrollable
    {

    public:
        void scroll(sf::Mouse::Wheel wheel = sf::Mouse::Wheel::VerticalWheel, f32t delta = 0, i32t x = 0, i32t y = 0);

        Scrollable() = default;
        virtual ~Scrollable() = default;

    protected:
        virtual void onScroll(const sf::Event &event) = 0;
    };

}
