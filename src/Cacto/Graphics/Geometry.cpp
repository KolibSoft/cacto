#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Lang/JsonConverter.hpp>
#include <Cacto/Graphics/Geometry.hpp>

namespace cacto
{

    JsonValue toJson(const Geometry *const &geometry)
    {
        auto json = JsonConverter<Geometry>::json(geometry);
        return std::move(json);
    }

    void fromJson(Geometry *&geometry, const JsonValue &json)
    {
        auto _geometry = JsonConverter<Geometry>::value(json);
        geometry = _geometry;
    }

    namespace geometry
    {

        JsonValue JsonConverter::toJson(const Line *const value) const
        {
            return toJson(dynamic_cast<const Geometry *>(value));
        }

    }

}