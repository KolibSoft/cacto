#include <SFML/Window/Event.hpp>
#include <Cacto/Window/Focusable.hpp>

namespace cacto
{

    void Focusable::focus()
    {
        sf::Event event{};
        event.type = sf::Event::GainedFocus;
        onFocus(event);
    }

    void Focusable::unfocus()
    {
        sf::Event event{};
        event.type = sf::Event::LostFocus;
        onUnfocus(event);
    }

}