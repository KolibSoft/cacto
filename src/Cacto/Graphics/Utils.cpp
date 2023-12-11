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
        else
            throw std::runtime_error("Unsupported primitive type");
    }

    std::string toString(const sf::Vector2f &point)
    {
        std::stringstream stream{};
        stream << point.x << ',' << point.y;
        return stream.str();
    }

    void fromString(sf::Vector2f &point, const std::string &string)
    {
        std::stringstream stream{string};
        stream >> point.x;
        stream.get();
        stream >> point.y;
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

    JsonValue toJson(const sf::FloatRect &rect)
    {
        JsonValue json = {rect.left, rect.top, rect.width, rect.height};
        return json;
    }

    void fromJson(sf::FloatRect &rect, const JsonValue &json)
    {
        rect.left = json.get(0).getNumber();
        rect.top = json.get(1).getNumber();
        rect.width = json.get(2).getNumber();
        rect.height = json.get(3).getNumber();
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
            item["position"] = {vertex.position.x, vertex.position.y};
            item["color"] = cacto::toString(vertex.color);
            item["texCoords"] = {vertex.texCoords.x, vertex.texCoords.y};
            vertexes.push_back(item);
        }
        return json;
    }

    void fromJson(sf::VertexArray &array, const JsonValue &json)
    {
        array.clear();
        sf::PrimitiveType primitive;
        fromString(primitive, json.get("primitive").getString("Points"));
        array.setPrimitiveType(sf::PrimitiveType::Triangles);
        auto &vertexes = json.get("vertexes");
        if (vertexes.isArray())
            for (auto &item : vertexes.asArray())
            {
                auto &position = item.get("position");
                auto &color = item.get("color");
                auto &texCoords = item.get("texCoords");
                sf::Vertex vertex{};
                vertex.position = {f32t(position.get(0).getNumber()), f32t(position.get(1).getNumber())};
                cacto::fromString(vertex.color, color.getString("#FFFFFFFF"));
                vertex.texCoords = {f32t(texCoords.get(0).getNumber()), f32t(texCoords.get(1).getNumber())};
                array.append(vertex);
            }
    }

    XmlValue toXml(const sf::Vertex &vertex)
    {
        XmlValue xml{"Vertex", {}};
        auto &attributes = xml.asAttributes();
        attributes["position"] = cacto::toString(vertex.position);
        attributes["color"] = cacto::toString(vertex.color);
        attributes["texCoords"] = cacto::toString(vertex.texCoords);
        return xml;
    }

    void fromXml(sf::Vertex &vertex, const XmlValue &xml)
    {
        vertex = {};
        auto position = xml.getAttribute("position", "0,0");
        auto texCoords = xml.getAttribute("texCoords", "0,0");
        auto color = xml.getAttribute("color", "#FFFFFFFF");
        cacto::fromString(vertex.position, position);
        cacto::fromString(vertex.color, color);
        cacto::fromString(vertex.texCoords, texCoords);
    }

}