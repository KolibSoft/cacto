#pragma once

#include <string>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <Cacto/Graphics/TextDirection.hpp>
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

    class Transform;
    class Transformable;
    class Angle;

    class String;
    class Font;

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

    void CACTO_GRAPHICS_API setGlyphs(sf::Vertex *const vertexes, const sf::Font &font, const sf::String &string, TextDirection direction, u32t characterSize, bool bold, f32t outlineThickness, szt count);
    void CACTO_GRAPHICS_API setGlyphs(sf::VertexArray &array, const sf::Font &font, const sf::String &string, TextDirection direction, u32t characterSize, bool bold, f32t outlineThickness);

    bool CACTO_GRAPHICS_API zoneIn(const sf::FloatRect &rect, const sf::FloatRect &zone);
    bool CACTO_GRAPHICS_API zoneWith(const sf::FloatRect &rect, const sf::FloatRect &zone);

    sf::Vector2f CACTO_GRAPHICS_API fitSize(const sf::Vector2f &contentSize, const sf::Vector2f &containerSize);

    std::string CACTO_GRAPHICS_API toString(const sf::PrimitiveType &primitive);
    void CACTO_GRAPHICS_API fromString(sf::PrimitiveType &primitive, const std::string &string);

    std::string CACTO_GRAPHICS_API toString(const sf::Vector2f &point);
    void CACTO_GRAPHICS_API fromString(sf::Vector2f &point, const std::string &string);

    std::string CACTO_GRAPHICS_API toString(const sf::FloatRect &rect);
    void CACTO_GRAPHICS_API fromString(sf::FloatRect &rect, const std::string &string);

    std::string CACTO_GRAPHICS_API toString(const sf::Color &color);
    void CACTO_GRAPHICS_API fromString(sf::Color &color, const std::string &string);

    XmlValue CACTO_GRAPHICS_API toXml(const sf::Vertex &vertex);
    void CACTO_GRAPHICS_API fromXml(sf::Vertex &vertex, const XmlValue &xml);

    XmlValue CACTO_GRAPHICS_API toXml(const sf::VertexArray &array);
    void CACTO_GRAPHICS_API fromXml(sf::VertexArray &array, const XmlValue &xml);

    XmlValue CACTO_GRAPHICS_API toXml(const sf::Transform &transform);
    void CACTO_GRAPHICS_API fromXml(sf::Transform &transform, const XmlValue &xml);

    XmlValue CACTO_GRAPHICS_API toXml(const sf::Transformable &transformable);
    void CACTO_GRAPHICS_API fromXml(sf::Transformable &transformable, const XmlValue &xml);

}
