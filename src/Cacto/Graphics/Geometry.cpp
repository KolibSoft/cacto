#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Lang/JsonConverter.hpp>
#include <Cacto/Graphics/Geometry.hpp>

namespace cacto
{

    JsonValue toJson(const Geometry *const &geometry)
    {
        if (geometry == nullptr)
            return nullptr;
        for (auto &converter : JsonConverter<Geometry>::Converters)
        {
            auto json = converter->toJson(geometry);
            if (json != nullptr)
                return json;
        }
        return nullptr;
    }

    void fromJson(Geometry *&geometry, const JsonValue &json)
    {
        if (json == nullptr)
            geometry = nullptr;
        for (auto &converter : JsonConverter<Geometry>::Converters)
        {
            geometry = converter->fromJson(json);
            if (geometry)
                return;
        }
    }

}