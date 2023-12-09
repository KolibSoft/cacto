#ifndef CACTO_GRAPHICS_UTILS_HPP
#define CACTO_GRAPHICS_UTILS_HPP

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

    class JsonValue;
    class XmlValue;

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

    sf::Vector2f CACTO_GRAPHICS_API fitSize(const sf::Vector2f &contentSize, const sf::Vector2f &containerSize);

    JsonValue CACTO_GRAPHICS_API toJson(const sf::FloatRect &rect);
    void CACTO_GRAPHICS_API fromJson(sf::FloatRect &rect, const JsonValue &json);

    JsonValue CACTO_GRAPHICS_API toJson(const sf::PrimitiveType &primitive);
    void CACTO_GRAPHICS_API fromJson(sf::PrimitiveType &primitive, const JsonValue &json);

    JsonValue CACTO_GRAPHICS_API toJson(const sf::VertexArray &array);
    void CACTO_GRAPHICS_API fromJson(sf::VertexArray &array, const JsonValue &json);

    XmlValue CACTO_GRAPHICS_API toXml(const sf::Vertex &vertex);
    void CACTO_GRAPHICS_API fromXml(sf::Vertex &vertex, const XmlValue &xml);

}

#endif