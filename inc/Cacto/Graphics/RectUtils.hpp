#pragma once

#include <string>
#include <ostream>
#include <istream>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{

    template <typename T>
    class Rect;

    using FloatRect = Rect<float>;

}

namespace cacto
{

    bool CACTO_GRAPHICS_API zoneIn(const sf::FloatRect &rect, const sf::FloatRect &zone);
    bool CACTO_GRAPHICS_API zoneWith(const sf::FloatRect &rect, const sf::FloatRect &zone);

    std::string CACTO_GRAPHICS_API toString(const sf::FloatRect &rect);
    sf::FloatRect CACTO_GRAPHICS_API toRect(const std::string &string);

    std::ostream &CACTO_GRAPHICS_API operator<<(std::ostream &stream, const sf::FloatRect &rect);
    std::istream &CACTO_GRAPHICS_API operator>>(std::istream &stream, sf::FloatRect &rect);

}