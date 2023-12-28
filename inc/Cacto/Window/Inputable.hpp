#pragma once

#include <Cacto/Config.hpp>

namespace sf
{
    class Event;
}

namespace cacto
{

    class Inputable
    {

    public:
        virtual void input(u32t unicode) = 0;

        Inputable() = default;
        virtual ~Inputable() = default;

    protected:
        virtual void onInput(const sf::Event &event) = 0;
    };

}
