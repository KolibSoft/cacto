#pragma once

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

    class JsonValue;

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

    JsonValue CACTO_GRAPHICS_API toJson(const Shared<const Geometry> &geometry);
    void CACTO_GRAPHICS_API fromJson(Shared<Geometry> &geometry, const JsonValue &json);

    namespace geometry
    {

        class CACTO_GRAPHICS_API LineJsonConverter
            : public virtual line::JsonConverter
        {
        public:
            JsonValue toJson(const Shared<const Line> &value) const override;
            Shared<Line> fromJson(const JsonValue &json) const override;

            LineJsonConverter() = default;
            virtual ~LineJsonConverter() = default;
        };

        extern LineJsonConverter CACTO_GRAPHICS_API LineConverter;

        class CACTO_GRAPHICS_API JsonConverter
            : public virtual cacto::JsonConverter<Geometry>
        {
        public:
            JsonConverter() = default;
            virtual ~JsonConverter() = default;
        };

    }

}
