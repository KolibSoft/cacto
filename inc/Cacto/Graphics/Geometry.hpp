#ifndef CACTO_GEOMETRY_HPP
#define CACTO_GEOMETRY_HPP

#include <SFML/Graphics/Rect.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class Vertex;
    class VertexArray;
}

namespace cacto
{

    class Geometry
    {

    public:
        virtual szt getPointCount() const = 0;
        virtual sf::Vector2f getPoint(szt index, szt precision = 0) const = 0;

        virtual sf::FloatRect getBounds() const = 0;
        virtual bool containsPoint(const sf::Vector2f &point) const = 0;

        Geometry() = default;
        virtual ~Geometry() = default;
    };

    void CACTO_GRAPHICS_API setPoints(sf::Vertex *const vertexes, const Geometry &geometry, szt count, szt precision = 0);
    void CACTO_GRAPHICS_API setPoints(sf::VertexArray &array, const Geometry &geometry, szt precision = 0);

}

#endif