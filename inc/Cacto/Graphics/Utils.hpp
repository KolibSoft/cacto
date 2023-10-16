#ifndef CACTO_GRAPHICS_UTILS_HPP
#define CACTO_GRAPHICS_UTILS_HPP

#include <vector>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{

    template <typename T>
    class Vector2;

    using Vector2f = Vector2<cacto::f32t>;

    template <typename T>
    class Rect;

    using FloatRect = Rect<cacto::f32t>;

    class Color;
    class Vertex;
    class VertexArray;

}

namespace cacto
{

    class PointSource;

    void CACTO_GRAPHICS_API setPositions(sf::Vertex *const vertexes, const sf::Vector2f *positions, szt count);
    void CACTO_GRAPHICS_API setPositions(sf::VertexArray &array, const std::vector<sf::Vector2f> &positions);

    void CACTO_GRAPHICS_API setColor(sf::Vertex *const vertexes, const sf::Color &color, szt count);
    void CACTO_GRAPHICS_API setColor(sf::VertexArray &array, const sf::Color &color);

    void CACTO_GRAPHICS_API setTexCoords(sf::Vertex *const vertexes, const sf::FloatRect bounds, const sf::FloatRect texRect, szt count);
    void CACTO_GRAPHICS_API setTexCoords(sf::VertexArray &array, const sf::FloatRect texRect);

    void CACTO_GRAPHICS_API mapPositions(sf::Vertex *const vertexes, const sf::FloatRect bounds, const sf::FloatRect surface, szt count);
    void CACTO_GRAPHICS_API mapPositions(sf::VertexArray &array, const sf::FloatRect surface);

    bool CACTO_GRAPHICS_API zoneIn(const sf::FloatRect &rect, const sf::FloatRect &zone);
    bool CACTO_GRAPHICS_API zoneWith(const sf::FloatRect &rect, const sf::FloatRect &zone);

}

#endif