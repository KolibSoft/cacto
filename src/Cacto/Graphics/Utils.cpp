#include <SFML/System/String.hpp>
#include <SFML/Graphics/Glyph.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Lang/Utils.hpp>
#include <Cacto/Graphics/ColorPack.hpp>
#include <Cacto/Graphics/Utils.hpp>

namespace cacto
{

    void setPositions(sf::Vertex *const vertexes, const sf::Vector2f *positions, szt count)
    {
        for (szt i = 0; i < count; i++)
        {
            vertexes[i].position = positions[i];
        }
    }

    void setPositions(sf::VertexArray &array, const std::vector<sf::Vector2f> &positions)
    {
        auto count = positions.size();
        array.resize(count);
        auto *vertexes = &(array[0]);
        auto *_points = &(positions[0]);
        setPositions(vertexes, _points, count);
    }

    void setColor(sf::Vertex *const vertexes, const sf::Color &color, szt count)
    {
        for (szt i = 0; i < count; i++)
        {
            vertexes[i].color = color;
        }
    }

    void setColor(sf::VertexArray &array, const sf::Color &color)
    {
        auto count = array.getVertexCount();
        auto *vertexes = &(array[0]);
        setColor(vertexes, color, count);
    }

    void setTexCoords(sf::Vertex *const vertexes, const sf::FloatRect bounds, const sf::FloatRect texRect, szt count)
    {
        for (szt i = 0; i < count; i++)
        {
            auto &position = vertexes[i].position;
            auto &texCoords = vertexes[i].texCoords;
            texCoords.x = (position.x - bounds.left) * (texRect.width / bounds.width) + texRect.left;
            texCoords.y = (position.y - bounds.top) * (texRect.height / bounds.height) + texRect.top;
        }
    }

    void setTexCoords(sf::VertexArray &array, const sf::FloatRect texRect)
    {
        auto count = array.getVertexCount();
        auto *vertexes = &(array[0]);
        auto bounds = array.getBounds();
        setTexCoords(vertexes, bounds, texRect, count);
    }

    void mapPositions(sf::Vertex *const vertexes, const sf::FloatRect bounds, const sf::FloatRect surface, szt count)
    {
        for (szt i = 0; i < count; i++)
        {
            auto &position = vertexes[i].position;
            position.x = (position.x - bounds.left) * (surface.width / bounds.width) + surface.left;
            position.y = (position.y - bounds.top) * (surface.height / bounds.height) + surface.top;
        }
    }

    void mapPositions(sf::VertexArray &array, const sf::FloatRect surface)
    {
        auto count = array.getVertexCount();
        auto *vertexes = &(array[0]);
        auto bounds = array.getBounds();
        mapPositions(vertexes, bounds, surface, count);
    }

    void setGlyphs(sf::Vertex *const vertexes, const sf::Font &font, const sf::String &string, TextDirection direction, u32t characterSize, bool bold, f32t outlineThickness, szt count)
    {
        count /= 6;
        f32t offset = 0;
        sf::Vertex glyph_vertexes[4]{};

        auto setTexCoords = [&](const sf::IntRect &rect)
        {
            sf::FloatRect _rect{rect};
            glyph_vertexes[0].texCoords = {_rect.left, _rect.top};
            glyph_vertexes[1].texCoords = {_rect.left + _rect.width, _rect.top};
            glyph_vertexes[2].texCoords = {_rect.left, _rect.top + _rect.height};
            glyph_vertexes[3].texCoords = {_rect.left + _rect.width, _rect.top + _rect.height};
        };

        auto appendGlyph = [&](szt i)
        {
            vertexes[i * 6 + 0] = glyph_vertexes[0];
            vertexes[i * 6 + 1] = glyph_vertexes[1];
            vertexes[i * 6 + 2] = glyph_vertexes[3];
            vertexes[i * 6 + 3] = glyph_vertexes[0];
            vertexes[i * 6 + 4] = glyph_vertexes[2];
            vertexes[i * 6 + 5] = glyph_vertexes[3];
        };

        switch (direction)
        {
        case TextDirection::ToLeft:
            for (szt i = 0; i < count; i++)
            {
                auto &glyph = font.getGlyph(string[i], characterSize, bold, outlineThickness);
                auto &bounds = glyph.bounds;

                offset += glyph.advance + font.getKerning(string[i], string[i + 1], characterSize, bold);
                glyph_vertexes[0].position = {bounds.left - offset, bounds.top};
                glyph_vertexes[1].position = {bounds.left + bounds.width - offset, bounds.top};
                glyph_vertexes[2].position = {bounds.left - offset, bounds.top + bounds.height};
                glyph_vertexes[3].position = {bounds.left + bounds.width - offset, bounds.top + bounds.height};

                setTexCoords(glyph.textureRect);
                appendGlyph(i);
            }
            break;
        case TextDirection::ToRight:
            for (szt i = 0; i < count; i++)
            {
                auto &glyph = font.getGlyph(string[i], characterSize, bold, outlineThickness);
                auto &bounds = glyph.bounds;

                glyph_vertexes[0].position = {bounds.left + offset, bounds.top};
                glyph_vertexes[1].position = {bounds.left + bounds.width + offset, bounds.top};
                glyph_vertexes[2].position = {bounds.left + offset, bounds.top + bounds.height};
                glyph_vertexes[3].position = {bounds.left + bounds.width + offset, bounds.top + bounds.height};
                offset += glyph.advance + font.getKerning(string[i], string[i + 1], characterSize, bold);

                setTexCoords(glyph.textureRect);
                appendGlyph(i);
            }
            break;
        case TextDirection::ToTop:
            for (szt i = 0; i < count; i++)
            {
                auto &glyph = font.getGlyph(string[i], characterSize, bold, outlineThickness);
                auto &bounds = glyph.bounds;

                offset += font.getLineSpacing(characterSize);
                glyph_vertexes[0].position = {bounds.left, bounds.top - offset};
                glyph_vertexes[1].position = {bounds.left + bounds.width, bounds.top - offset};
                glyph_vertexes[2].position = {bounds.left, bounds.top + bounds.height - offset};
                glyph_vertexes[3].position = {bounds.left + bounds.width, bounds.top + bounds.height - offset};

                setTexCoords(glyph.textureRect);
                appendGlyph(i);
            }
            break;
        case TextDirection::ToBottom:
            for (szt i = 0; i < count; i++)
            {
                auto &glyph = font.getGlyph(string[i], characterSize, bold, outlineThickness);
                auto &bounds = glyph.bounds;

                glyph_vertexes[0].position = {bounds.left, bounds.top + offset};
                glyph_vertexes[1].position = {bounds.left + bounds.width, bounds.top + offset};
                glyph_vertexes[2].position = {bounds.left, bounds.top + bounds.height + offset};
                glyph_vertexes[3].position = {bounds.left + bounds.width, bounds.top + bounds.height + offset};
                offset += font.getLineSpacing(characterSize);

                setTexCoords(glyph.textureRect);
                appendGlyph(i);
            }
            break;
        }
    }

    void setGlyphs(sf::VertexArray &array, const sf::Font &font, const sf::String &string, TextDirection direction, u32t characterSize, bool bold, f32t outlineThickness)
    {
        array.resize(string.getSize() * 6);
        auto count = array.getVertexCount();
        auto *vertexes = &(array[0]);
        setGlyphs(vertexes, font, string, direction, characterSize, bold, outlineThickness, count);
    }

    bool zoneIn(const sf::FloatRect &rect, const sf::FloatRect &zone)
    {
        auto _rectRight = rect.left + rect.width;
        auto _rectBottom = rect.top + rect.height;

        auto _zoneRight = zone.left + zone.width;
        auto _zoneBottom = zone.top + zone.height;

        auto rectLeft = std::min(rect.left, _rectRight);
        auto rectTop = std::min(rect.top, _rectBottom);
        auto rectRight = std::max(rect.left, _rectRight);
        auto rectBottom = std::max(rect.top, _rectBottom);

        auto zoneLeft = std::min(zone.left, _zoneRight);
        auto zoneTop = std::min(zone.top, _zoneBottom);
        auto zoneRight = std::max(zone.left, _zoneRight);
        auto zoneBottom = std::max(zone.top, _zoneBottom);

        auto result = rectLeft <= zoneLeft && rectTop <= zoneTop && rectRight >= zoneRight && rectBottom >= zoneBottom;
        return result;
    }

    bool zoneWith(const sf::FloatRect &rect, const sf::FloatRect &zone)
    {
        auto _rectRight = rect.left + rect.width;
        auto _rectBottom = rect.top + rect.height;

        auto _zoneRight = zone.left + zone.width;
        auto _zoneBottom = zone.top + zone.height;

        auto rectLeft = std::min(rect.left, _rectRight);
        auto rectTop = std::min(rect.top, _rectBottom);
        auto rectRight = std::max(rect.left, _rectRight);
        auto rectBottom = std::max(rect.top, _rectBottom);

        auto zoneLeft = std::min(zone.left, _zoneRight);
        auto zoneTop = std::min(zone.top, _zoneBottom);
        auto zoneRight = std::max(zone.left, _zoneRight);
        auto zoneBottom = std::max(zone.top, _zoneBottom);

        auto result = rectLeft <= zoneRight && rectTop <= zoneBottom && rectRight >= zoneLeft && rectBottom >= zoneTop;
        return result;
    }

    sf::Vector2f fitSize(const sf::Vector2f &contentSize, const sf::Vector2f &containerSize)
    {
        sf::Vector2f size{0, 0};
        auto hRatio = contentSize.x / containerSize.x;
        auto vRatio = contentSize.y / containerSize.y;
        if (hRatio < vRatio)
        {
            size.y = containerSize.y;
            size.x = containerSize.y * contentSize.x / contentSize.y;
        }
        else if (vRatio < hRatio)
        {
            size.x = containerSize.x;
            size.y = containerSize.x * contentSize.y / contentSize.x;
        }
        else
        {
            size = containerSize;
        }
        return size;
    }

    std::string toString(const sf::PrimitiveType &primitive)
    {
        if (primitive == sf::PrimitiveType::Points)
            return "Points";
        else if (primitive == sf::PrimitiveType::Lines)
            return "Lines";
        else if (primitive == sf::PrimitiveType::LineStrip)
            return "LineStrip";
        else if (primitive == sf::PrimitiveType::Triangles)
            return "Triangles";
        else if (primitive == sf::PrimitiveType::TriangleStrip)
            return "TriangleStrip";
        else if (primitive == sf::PrimitiveType::TriangleFan)
            return "TriangleFan";
        else
            throw std::runtime_error("Unsupported primitive type");
    }

    void fromString(sf::PrimitiveType &primitive, const std::string &string)
    {
        if (string == "Points")
            primitive = sf::PrimitiveType::Points;
        else if (string == "Lines")
            primitive = sf::PrimitiveType::Lines;
        else if (string == "LineStrip")
            primitive = sf::PrimitiveType::LineStrip;
        else if (string == "Triangles")
            primitive = sf::PrimitiveType::Triangles;
        else if (string == "TriangleStrip")
            primitive = sf::PrimitiveType::TriangleStrip;
        else if (string == "TriangleFan")
            primitive = sf::PrimitiveType::TriangleFan;
        else
            throw std::runtime_error("Unsupported primitive type");
    }

    std::string toString(const sf::Vector2f &point)
    {
        std::stringstream stream{};
        char separator = ',';
        stream << point.x << separator << point.y;
        return stream.str();
    }

    void fromString(sf::Vector2f &point, const std::string &string)
    {
        std::stringstream stream{string};
        char separator = ',';
        stream >> point.x >> separator >> point.y;
    }

    std::string toString(const sf::FloatRect &rect)
    {
        std::stringstream stream{};
        char separator = ',';
        stream << rect.left << separator << rect.top << separator << rect.width << separator << rect.height;
        return stream.str();
    }

    void fromString(sf::FloatRect &rect, const std::string &string)
    {
        std::stringstream stream{string};
        char separator = ',';
        stream >> rect.left >> separator >> rect.top >> separator >> rect.width >> separator >> rect.height;
    }

    std::string toString(const sf::Color &color)
    {
        std::stringstream stream{};
        stream << '#' << std::hex << std::setw(8) << std::setfill('0') << std::uppercase << color.toInteger();
        return stream.str();
    }

    void fromString(sf::Color &color, const std::string &string)
    {
        std::stringstream stream{string};
        stream.get();
        u32t integer;
        stream >> std::hex >> integer;
        color = sf::Color(integer);
    }

    XmlValue toXml(const sf::Vertex &vertex)
    {
        XmlValue xml{"Vertex", {}};
        xml["position"] = cacto::toString(vertex.position);
        xml["texCoords"] = cacto::toString(vertex.texCoords);
        xml["color"] = toAttribute(vertex.color);
        return std::move(xml);
    }

    void fromXml(sf::Vertex &vertex, const XmlValue &xml)
    {
        vertex = {};
        auto position = xml.getAttribute("position", "0,0");
        auto texCoords = xml.getAttribute("texCoords", "0,0");
        auto color = xml.getAttribute("color");
        cacto::fromString(vertex.position, position);
        cacto::fromString(vertex.texCoords, texCoords);
        vertex.color = fromAttribute(color);
    }

    XmlValue toXml(const sf::VertexArray &array)
    {
        XmlValue xml{"VertexArray", {}};
        auto &content = xml.asContent();
        xml["primitive"] = cacto::toString(array.getPrimitiveType());
        for (szt i = 0; i < array.getVertexCount(); i++)
        {
            auto &vertex = array[i];
            auto vertex_xml = cacto::toXml(vertex);
            content.push_back(std::move(vertex_xml));
        }
        return std::move(xml);
    }

    void fromXml(sf::VertexArray &array, const XmlValue &xml)
    {
        array = {};
        sf::PrimitiveType primitive;
        cacto::fromString(primitive, xml.getAttribute("primitive", "Points"));
        array.setPrimitiveType(primitive);
        if (xml.isTag())
            for (auto &vertex_xml : xml.asContent())
            {
                sf::Vertex vertex{};
                cacto::fromXml(vertex, vertex_xml);
                array.append(vertex);
            }
    }

    XmlValue toXml(const sf::Transform &transform)
    {
        auto matrix = transform.getMatrix();
        f32t values[9]{matrix[0], matrix[4], matrix[12],
                       matrix[1], matrix[5], matrix[13],
                       matrix[3], matrix[7], matrix[15]};
        char separator = ',';
        std::stringstream stream{};
        stream << values[0] << separator << values[1] << separator << values[2] << separator << values[3] << separator << values[4] << separator << values[5] << separator << values[6] << separator << values[7] << separator << values[8];
        std::string _matrix{stream.str()};
        XmlValue xml{"Transform", {}};
        xml["matrix"] = _matrix;
        return std::move(xml);
    }

    void fromXml(sf::Transform &transform, const XmlValue &xml)
    {
        transform = {};
        auto matrix = xml.getAttribute("matrix", "1,0,0,0,1,0,0,0,1");
        f32t values[9]{};
        char separator = ',';
        std::stringstream stream{matrix};
        stream >> values[0] >> separator >> values[1] >> separator >> values[2] >> separator >> values[3] >> separator >> values[4] >> separator >> values[5] >> separator >> values[6] >> separator >> values[7] >> separator >> values[8];
        transform = sf::Transform(values[0], values[1], values[2],
                                  values[3], values[4], values[5],
                                  values[6], values[7], values[8]);
        if (xml.isTag())
            for (auto &item : xml.asContent())
                if (item.isTag())
                {
                    if (item.getName() == "Scale")
                    {
                        sf::Vector2f factors{};
                        fromString(factors, item.getAttribute("factors", "1,1"));
                        transform.scale(factors);
                    }
                    else if (item.getName() == "Translate")
                    {
                        sf::Vector2f offset{};
                        fromString(offset, item.getAttribute("offset", "0,0"));
                        transform.translate(offset);
                    }
                    else if (item.getName() == "Rotate")
                    {
                        sf::Angle angle{};
                        angle = sf::degrees(std::stof(item.getAttribute("degrees", "0"))) + sf::radians(std::stof(xml.getAttribute("radians", "0")));
                        transform.rotate(angle);
                    }
                }
    }

    XmlValue toXml(const sf::Transformable &transformable)
    {
        XmlValue xml{"Transformable", {}};
        xml["origin"] = toString(transformable.getOrigin());
        xml["scale"] = toString(transformable.getScale());
        xml["position"] = toString(transformable.getPosition());
        xml["rotation"] = std::to_string(transformable.getRotation().asDegrees());
        return std::move(xml);
    }

    void fromXml(sf::Transformable &transformable, const XmlValue &xml)
    {
        sf::Vector2f origin{};
        sf::Vector2f scale{};
        sf::Vector2f position{};
        f32t rotation{};
        fromString(origin, xml.getAttribute("origin", "0,0"));
        fromString(scale, xml.getAttribute("scale", "1,1"));
        fromString(position, xml.getAttribute("position", "0,0"));
        rotation = std::stof(xml.getAttribute("rotation", "0"));
        transformable.setOrigin(origin);
        transformable.setScale(scale);
        transformable.setPosition(position);
        transformable.setRotation(sf::degrees(rotation));
        if (xml.isTag())
            for (auto &item : xml.asContent())
                if (item.isTag())
                {
                    if (item.getName() == "Scale")
                    {
                        sf::Vector2f factors{};
                        fromString(factors, item.getAttribute("factors", "0,0"));
                        transformable.scale(factors);
                    }
                    else if (item.getName() == "Translate" || item.getName() == "Move")
                    {
                        sf::Vector2f offset{};
                        fromString(offset, item.getAttribute("offset", "0,0"));
                        transformable.move(offset);
                    }
                    else if (item.getName() == "Rotate")
                    {
                        sf::Angle angle{};
                        angle = sf::degrees(std::stof(item.getAttribute("degrees", "0"))) + sf::radians(std::stof(xml.getAttribute("radians", "0")));
                        transformable.rotate(angle);
                    }
                }
    }

}