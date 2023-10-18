#ifndef CACTO_LINE_HPP
#define CACTO_LINE_HPP

#include <SFML/System/Vector2.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class Vertex;
    class VertexArray;
}

namespace cacto
{

    class Line
    {

    public:
        virtual szt getSideCount() const = 0;
        virtual sf::Vector2f getPoint(szt index, szt precision = 1) const = 0;

        Line() = default;
        virtual ~Line() = default;
    };

    void CACTO_GRAPHICS_API setPoints(sf::Vertex *const vertexes, const Line &line, szt count, szt precision = 0);
    void CACTO_GRAPHICS_API setPoints(sf::VertexArray &array, const Line &line, szt precision = 0);

}

#endif