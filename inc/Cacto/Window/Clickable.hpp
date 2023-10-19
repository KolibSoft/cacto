#ifndef CACTO_CLICKABLE_HPP
#define CACTO_CLICKABLE_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <Cacto/Window/Export.hpp>

namespace sf
{
    class Event;
}

namespace cacto
{

    class CACTO_WINDOW_API Clickable
    {
    public:
        void click(sf::Mouse::Button button = sf::Mouse::Left, const sf::Vector2f &position = {0, 0});

        Clickable() = default;
        virtual ~Clickable() = default;

    protected:
        virtual void onClick(const sf::Event &event) = 0;
    };

}

#endif