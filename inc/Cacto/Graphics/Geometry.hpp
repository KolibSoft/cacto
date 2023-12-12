#ifndef CACTO_GEOMETRY_HPP
#define CACTO_GEOMETRY_HPP

#include <Cacto/Lang/JsonConverter.hpp>
#include <Cacto/Graphics/Line.hpp>

namespace sf
{

    template <typename T>
    class Rect;

    using FloatRect = Rect<float>;

}

namespace cacto
{

    class Geometry
        : public virtual Line
    {

    public:
        virtual sf::FloatRect getBounds() const = 0;
        virtual bool containsPoint(const sf::Vector2f &point) const = 0;

        Geometry() = default;
        virtual ~Geometry() = default;
    };

    template class CACTO_GRAPHICS_API cacto::JsonConverter<Geometry>;

    namespace geometry
    {
        class CACTO_GRAPHICS_API JsonConverter
            : public virtual line::JsonConverter,
              public virtual cacto::JsonConverter<Geometry>
        {
        public:
            JsonValue toJson(const Line *const value) const override;

            JsonConverter() = default;
            virtual ~JsonConverter() = default;
        };
    }

}

#endif