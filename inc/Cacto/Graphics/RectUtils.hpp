#pragma once

#include <string>
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
    void CACTO_GRAPHICS_API fromString(sf::FloatRect &rect, const std::string &string);

    std::string CACTO_GRAPHICS_API toAttribute(const sf::FloatRect &rect);
    void CACTO_GRAPHICS_API fromAttribute(sf::FloatRect &rect, const std::string &attribute);

}