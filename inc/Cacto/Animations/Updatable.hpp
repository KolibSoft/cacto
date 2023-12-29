#pragma once

namespace sf
{
    class Time;
}

namespace cacto
{

    class Updatable
    {

    public:
        virtual void update(const sf::Time &time) = 0;

        Updatable() = default;
        virtual ~Updatable() = default;
    };

}