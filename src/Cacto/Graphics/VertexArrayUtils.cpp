#include <SFML/System/String.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Font.hpp>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Graphics/VectorUtils.hpp>
#include <Cacto/Graphics/VertexArrayUtils.hpp>

namespace cacto
{

    void setPositions(sf::Vertex *const vertexes, const sf::Vector2f *positions, szt count)
    {
        for (szt i = 0; i < count; i++)
            vertexes[i].position = positions[i];
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
            vertexes[i].color = color;
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
            texCoords = mapPoint(position, bounds, texRect);
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
            position = mapPoint(position, bounds, surface);
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

    XmlValue toXml(const sf::Vertex &vertex)
    {
        XmlValue xml{"Vertex", {}};
        xml["position"] = cacto::toString(vertex.position);
        xml["texCoords"] = cacto::toString(vertex.texCoords);
        xml["color"] = cacto::toAttribute(vertex.color);
        return std::move(xml);
    }

    void fromXml(sf::Vertex &vertex, const XmlValue &xml)
    {
        vertex = {};
        auto position = xml.getAttribute("position", "0,0");
        auto texCoords = xml.getAttribute("texCoords", "0,0");
        auto color = xml.getAttribute("color", "#FFFFFFFF");
        cacto::fromString(vertex.position, position);
        cacto::fromString(vertex.texCoords, texCoords);
        cacto::fromAttribute(vertex.color, color);
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

}