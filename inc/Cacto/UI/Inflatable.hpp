#pragma once

#include <SFML/System/Vector2.hpp>

namespace cacto
{

    class Inflatable
    {

    public:
        virtual sf::Vector2f compact() = 0;
        virtual sf::Vector2f inflate(const sf::Vector2f &containerSize = {0, 0}) = 0;
        virtual void place(const sf::Vector2f &position = {0, 0}) = 0;

        Inflatable() = default;
        virtual ~Inflatable() = default;
    };

}