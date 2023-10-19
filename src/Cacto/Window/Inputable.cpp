#include <SFML/Window/Event.hpp>
#include <Cacto/Window/Inputable.hpp>

namespace cacto
{

    void Inputable::input(u32t unicode)
    {
        sf::Event event{};
        event.type = sf::Event::TextEntered;
        event.text.unicode = unicode;
        onInput(event);
    }

}