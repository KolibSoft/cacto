#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Lang/Utils.hpp>
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
    }

    JsonValue toJson(const sf::FloatRect &rect)
    {
        JsonValue json = {rect.left, rect.top, rect.width, rect.height};
        return json;
    }

    void fromJson(sf::FloatRect &rect, const JsonValue &json)
    {
        rect.left = f32t(json[0].asNumber());
        rect.top = f32t(json[1].asNumber());
        rect.width = f32t(json[2].asNumber());
        rect.height = f32t(json[3].asNumber());
    }

    JsonValue toJson(const sf::VertexArray &array)
    {
        auto json = JsonValue::ObjectValue;
        auto primitive = array.getPrimitiveType();
        json["primitive"] = toString(primitive);
        auto &vertexes = (json["vertexes"] = JsonValue::ArrayValue).asArray();
        for (szt i = 0; i < array.getVertexCount(); i++)
        {
            auto &vertex = array[i];
            auto item = JsonValue::ObjectValue;
            item["position"] = {f64t(vertex.position.x), f64t(vertex.position.y)};
            item["color"] = {f64t(vertex.color.r), f64t(vertex.color.g), f64t(vertex.color.b), f64t(vertex.color.a)};
            item["texCoords"] = {f64t(vertex.texCoords.x), f64t(vertex.texCoords.y)};
            vertexes.push_back(item);
        }
        return json;
    }

    void fromJson(sf::VertexArray &array, const JsonValue &json)
    {
        array.clear();
        sf::PrimitiveType primitive;
        fromString(primitive, json["primitive"].asString());
        array.setPrimitiveType(sf::PrimitiveType::Triangles);
        auto &vertexes = json["vertexes"].asArray();
        for (auto &item : vertexes)
        {
            auto &position = item["position"];
            auto &color = item["color"];
            auto &texCoords = item["texCoords"];
            sf::Vertex vertex{};
            vertex.position = {f32t(position[0].asNumber()), f32t(position[1].asNumber())};
            vertex.color = {u8t(color[0].asNumber()), u8t(color[1].asNumber()), u8t(color[2].asNumber()), u8t(color[3].asNumber())};
            vertex.texCoords = {f32t(texCoords[0].asNumber()), f32t(texCoords[1].asNumber())};
            array.append(vertex);
        }
    }

    XmlValue toXml(const sf::Vertex &vertex)
    {
        XmlValue xml{"Vertex", {}};
        auto &attributes = xml.asAttributes();
        attributes["position"] = std::to_string(vertex.position.x) + "," + std::to_string(vertex.position.y);
        attributes["texCoords"] = std::to_string(vertex.texCoords.x) + "," + std::to_string(vertex.texCoords.y);
        attributes["color"] = std::to_string(vertex.color.r) + "," + std::to_string(vertex.color.g) + "," + std::to_string(vertex.color.b) + "," + std::to_string(vertex.color.a);
        return xml;
    }

    void fromXml(sf::Vertex &vertex, const XmlValue &xml)
    {
        auto &attributes = xml.asAttributes();
        auto position = split(attributes.at("position"), ',');
        auto texCoords = split(attributes.at("texCoords"), ',');
        auto color = split(attributes.at("color"), ',');
        vertex.position = {std::stof(position[0]), std::stof(position[1])};
        vertex.texCoords = {std::stof(texCoords[0]), std::stof(texCoords[1])};
        vertex.color = {u8t(std::stoi(color[0])), u8t(std::stoi(color[1])), u8t(std::stoi(color[2])), u8t(std::stoi(color[3]))};
    }

}