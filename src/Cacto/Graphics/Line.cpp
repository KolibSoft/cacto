#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Lang/JsonConverter.hpp>
#include <Cacto/Graphics/Line.hpp>

namespace cacto
{

    void setPoints(sf::Vertex *const vertexes, const Line &line, szt count, szt precision)
    {
        for (szt i = 0; i < count; i++)
            vertexes[i].position = line.getPoint(i, precision);
    }

    void setPoints(sf::VertexArray &array, const Line &line, szt precision)
    {
        if (precision < 1)
            precision = 1;
        auto count = line.getPointCount() * precision;
        array.resize(count);
        auto *vertexes = &(array[0]);
        setPoints(vertexes, line, count, precision);
    }

    JsonValue toJson(const Line *const &line)
    {
        if (line == nullptr)
            return nullptr;
        for (auto &converter : JsonConverter<Line>::Converters)
        {
            auto json = converter->toJson(line);
            if (json != nullptr)
                return json;
        }
        return nullptr;
    }

    void fromJson(Line *&line, const JsonValue &json)
    {
        if (json == nullptr)
            line = nullptr;
        for (auto &converter : JsonConverter<Line>::Converters)
        {
            line = converter->fromJson(json);
            if (line)
                return;
        }
    }

}