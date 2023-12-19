#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Lang/JsonConverter.hpp>
#include <Cacto/Graphics/Geometry.hpp>

namespace cacto
{

    JsonValue toJson(const Shared<const Geometry> &geometry)
    {
        auto json = JsonConverter<Geometry>::json(geometry);
        return std::move(json);
    }

    void fromJson(Shared<Geometry> &geometry, const JsonValue &json)
    {
        auto _geometry = JsonConverter<Geometry>::value(json);
        geometry = std::move(_geometry);
    }

    namespace geometry
    {

        JsonValue LineJsonConverter::toJson(const Shared<const Line> &value) const
        {
            try
            {
                auto cast = std::dynamic_pointer_cast<const Geometry>(value);
                auto json = cacto::JsonConverter<Geometry>::json(cast);
                return std::move(json);
            }
            catch (std::bad_cast)
            {
                return nullptr;
            }
        }

        Shared<Line> LineJsonConverter::fromJson(const JsonValue &json) const
        {
            auto value = cacto::JsonConverter<Geometry>::value(json);
            return std::move(value);
        }

        LineJsonConverter LineConverter;

    }

}