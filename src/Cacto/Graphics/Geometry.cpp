#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Lang/JsonConverter.hpp>
#include <Cacto/Graphics/Geometry.hpp>

namespace cacto
{

    namespace geometry
    {

        JsonValue JsonConverter::toJson(const Line *const value) const
        {
            return toJson(dynamic_cast<const Geometry *>(value));
        }

    }

}