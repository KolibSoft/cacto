#pragma once

#include <vector>
#include <Cacto/Graphics/TextDirection.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{

    template <typename T>
    class Vector2;

    using Vector2f = Vector2<float>;

    template <typename T>
    class Rect;

    using FloatRect = Rect<float>;

    class String;
    class Color;
    class Vertex;
    class VertexArray;
    class Font;

}

namespace cacto
{

    class XmlValue;

    void CACTO_GRAPHICS_API setPositions(sf::Vertex *const vertexes, const sf::Vector2f *positions, szt count);
    void CACTO_GRAPHICS_API setPositions(sf::VertexArray &array, const std::vector<sf::Vector2f> &positions);

    void CACTO_GRAPHICS_API setColor(sf::Vertex *const vertexes, szt count, const sf::Color &color);
    void CACTO_GRAPHICS_API setColor(sf::VertexArray &array, const sf::Color &color);

    void CACTO_GRAPHICS_API setTexCoords(sf::Vertex *const vertexes, szt count, const sf::FloatRect bounds, const sf::FloatRect texRect);
    void CACTO_GRAPHICS_API setTexCoords(sf::VertexArray &array, const sf::FloatRect texRect);

    void CACTO_GRAPHICS_API mapPositions(sf::Vertex *const vertexes, szt count, const sf::FloatRect bounds, const sf::FloatRect surface);
    void CACTO_GRAPHICS_API mapPositions(sf::VertexArray &array, const sf::FloatRect surface);

    void CACTO_GRAPHICS_API setGlyphs(sf::Vertex *const vertexes, const c32t *const codes, szt count, TextDirection direction, const sf::Font &font, u32t characterSize, bool bold, f32t outlineThickness);
    void CACTO_GRAPHICS_API setGlyphs(sf::VertexArray &array, const sf::String &string, TextDirection direction, const sf::Font &font, u32t characterSize, bool bold, f32t outlineThickness);

    XmlValue CACTO_GRAPHICS_API toXml(const sf::Vertex &vertex);
    sf::Vertex CACTO_GRAPHICS_API toVertex(const XmlValue &xml);

    XmlValue CACTO_GRAPHICS_API toXml(const sf::VertexArray &array);
    sf::VertexArray CACTO_GRAPHICS_API toVertexArray(const XmlValue &xml);

}