#include <SFML/Window/Event.hpp>
#include <Cacto/Window/Clickable.hpp>

namespace cacto
{

    void Clickable::click(sf::Mouse::Button button, const sf::Vector2f &position)
    {
        sf::Event event{};
        event.type = sf::Event::MouseButtonReleased;
        event.mouseButton.button = button;
        event.mouseButton.x = position.x;
        event.mouseButton.y = position.y;
        onClick(event);
    }

}