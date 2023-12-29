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

    void CACTO_GRAPHICS_API setColor(sf::Vertex *const vertexes, const sf::Color &color, szt count);
    void CACTO_GRAPHICS_API setColor(sf::VertexArray &array, const sf::Color &color);

    void CACTO_GRAPHICS_API setTexCoords(sf::Vertex *const vertexes, const sf::FloatRect bounds, const sf::FloatRect texRect, szt count);
    void CACTO_GRAPHICS_API setTexCoords(sf::VertexArray &array, const sf::FloatRect texRect);

    void CACTO_GRAPHICS_API mapPositions(sf::Vertex *const vertexes, const sf::FloatRect bounds, const sf::FloatRect surface, szt count);
    void CACTO_GRAPHICS_API mapPositions(sf::VertexArray &array, const sf::FloatRect surface);

    void CACTO_GRAPHICS_API setGlyphs(sf::Vertex *const vertexes, const sf::Font &font, const sf::String &string, TextDirection direction, u32t characterSize, bool bold, f32t outlineThickness, szt count);
    void CACTO_GRAPHICS_API setGlyphs(sf::VertexArray &array, const sf::Font &font, const sf::String &string, TextDirection direction, u32t characterSize, bool bold, f32t outlineThickness);

    XmlValue CACTO_GRAPHICS_API toXml(const sf::Vertex &vertex);
    void CACTO_GRAPHICS_API fromXml(sf::Vertex &vertex, const XmlValue &xml);

    XmlValue CACTO_GRAPHICS_API toXml(const sf::VertexArray &array);
    void CACTO_GRAPHICS_API fromXml(sf::VertexArray &array, const XmlValue &xml);

}