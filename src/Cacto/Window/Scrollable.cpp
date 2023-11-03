#include <SFML/Window/Event.hpp>
#include <Cacto/Window/Scrollable.hpp>

namespace cacto
{

    void Scrollable::scroll(sf::Mouse::Wheel wheel, f32t delta, i32t x, i32t y)
    {
        sf::Event event{};
        event.type = sf::Event::MouseWheelScrolled;
        event.mouseWheelScroll.wheel = wheel;
        event.mouseWheelScroll.delta = delta;
        event.mouseWheelScroll.x = x;
        event.mouseWheelScroll.y = y;
        onScroll(event);
    }

}