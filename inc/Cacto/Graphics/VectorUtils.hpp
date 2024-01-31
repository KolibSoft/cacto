#pragma once

#include <Cacto/Graphics/Export.hpp>

namespace sf
{

    template <typename T>
    class Vector2;

    using Vector2f = Vector2<float>;

    template <typename T>
    class Rect;

    using FloatRect = Rect<float>;

}

namespace cacto
{

    sf::Vector2f CACTO_GRAPHICS_API mapPoint(const sf::Vector2f &point, const sf::FloatRect &bounds, const sf::FloatRect &surface);
    sf::Vector2f CACTO_GRAPHICS_API fitSize(const sf::Vector2f &contentSize, const sf::Vector2f &containerSize);

}