#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Lang/JsonValue.hpp>
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

    void rectMapToFile(const std::unordered_map<std::string, sf::FloatRect> &map, const std::filesystem::path &path)
    {
        auto json = JsonValue::ObjectValue;
        for (auto &pair : map)
            json[pair.first] = {pair.second.left, pair.second.top, pair.second.width, pair.second.height};
        json.toFile(path);
    }

    std::unordered_map<std::string, sf::FloatRect> rectMapFromFile(const std::filesystem::path &path)
    {
        JsonValue json = nullptr;
        json.fromFile(path);
        std::unordered_map<std::string, sf::FloatRect> map{};
        for (auto &pair : json.asObject())
        {
            sf::FloatRect rect{{f32t(pair.second[0].asNumber()), f32t(pair.second[1].asNumber())},
                               {f32t(pair.second[2].asNumber()), f32t(pair.second[3].asNumber())}};
            map[pair.first] = rect;
        }
        return map;
    }

    void vertexArrayToFile(const sf::VertexArray &array, const std::filesystem::path &path)
    {
        auto json = JsonValue::ObjectValue;
        switch (array.getPrimitiveType())
        {
        case sf::PrimitiveType::Points:
            json["primitive"] = "Points";
            break;
        case sf::PrimitiveType::Lines:
            json["primitive"] = "Lines";
            break;
        case sf::PrimitiveType::LineStrip:
            json["primitive"] = "LineStrip";
            break;
        case sf::PrimitiveType::Triangles:
            json["primitive"] = "Triangles";
            break;
        case sf::PrimitiveType::TriangleStrip:
            json["primitive"] = "TriangleStrip";
            break;
        case sf::PrimitiveType::TriangleFan:
            json["primitive"] = "TriangleFan";
            break;
        };
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
        json.toFile(path);
    }

    sf::VertexArray vertexArrayFromFile(const std::filesystem::path &path)
    {
        JsonValue json = nullptr;
        json.fromFile(path);
        sf::VertexArray array{};
        auto &primitive = json["primitive"].asString();
        if (primitive == "Points")
            array.setPrimitiveType(sf::PrimitiveType::Points);
        else if (primitive == "Lines")
            array.setPrimitiveType(sf::PrimitiveType::Lines);
        else if (primitive == "LineStrip")
            array.setPrimitiveType(sf::PrimitiveType::LineStrip);
        else if (primitive == "Triangles")
            array.setPrimitiveType(sf::PrimitiveType::Triangles);
        else if (primitive == "TriangleStrip")
            array.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
        else if (primitive == "TriangleFan")
            array.setPrimitiveType(sf::PrimitiveType::TriangleFan);
        else
            throw std::runtime_error("Unsupported primitive type");
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
        return array;
    }

}