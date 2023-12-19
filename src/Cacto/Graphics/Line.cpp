#include <algorithm>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
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

}