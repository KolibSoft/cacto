#ifndef CACTO_LINE_HPP
#define CACTO_LINE_HPP

#include <Cacto/Lang/JsonConverter.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{

    template <typename T>
    class Vector2;

    using Vector2f = Vector2<float>;

    class Vertex;
    class VertexArray;
}

namespace cacto
{

    class CACTO_GRAPHICS_API Line
    {

    public:
        virtual szt getPointCount() const = 0;
        virtual sf::Vector2f getPoint(szt index, szt precision = 1) const = 0;

        Line() = default;
        virtual ~Line() = default;
    };

    template class CACTO_GRAPHICS_API cacto::JsonConverter<Line>;

    void CACTO_GRAPHICS_API setPoints(sf::Vertex *const vertexes, const Line &line, szt count, szt precision = 0);
    void CACTO_GRAPHICS_API setPoints(sf::VertexArray &array, const Line &line, szt precision = 0);

    namespace line
    {
        class CACTO_GRAPHICS_API JsonConverter
            : public virtual cacto::JsonConverter<Line>
        {
        public:
            JsonConverter() = default;
            virtual ~JsonConverter() = default;
        };
    }

}

#endif