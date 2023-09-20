#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Graphics/Geometry.hpp>

namespace cacto
{

    bool Geometry::intersects(const Geometry &other) const
    {
        auto pointCount = other.getPointCount();
        for (szt i = 0; i < pointCount; i++)
        {
            auto point = other.getPoint(i);
            if (containsPoint(point))
                return true;
        }
        pointCount = getPointCount();
        for (szt i = 0; i < pointCount; i++)
        {
            auto point = getPoint(i);
            if (other.containsPoint(point))
                return true;
        }
        return false;
    }

    void setPoints(sf::Vertex *const vertexes, const Geometry &geometry, szt count, szt precision)
    {
        for (szt i = 0; i < count; i++)
        {
            vertexes[i].position = geometry.getPoint(i, precision);
        }
    }

    void setPoints(sf::VertexArray &array, const Geometry &geometry, szt precision)
    {
        if (precision == 0)
        {
            precision = 1;
        }
        auto count = geometry.getPointCount() * precision;
        array.resize(count);
        auto *vertexes = &(array[0]);
        setPoints(vertexes, geometry, count, precision);
    }

}