#ifndef CACTO_LINE_HPP
#define CACTO_LINE_HPP

#include <SFML/System/Vector2.hpp>
#include <Cacto/Config.hpp>

namespace cacto
{

    class Line
    {

    public:
        virtual sf::Vector2f getPoint(szt index, szt precision = 1) const = 0;
        virtual sf::Vector2f getDirection(szt index, szt precision = 1) const = 0;

        Line() = default;
        virtual ~Line() = default;
    };

}

#endif