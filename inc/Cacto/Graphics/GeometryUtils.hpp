#pragma once

#include <string>
#include <Cacto/Graphics/Export.hpp>

namespace cacto
{

    class Geometry;

    std::string CACTO_GRAPHICS_API getExpression(const Geometry *geometry);
    const Geometry *CACTO_GRAPHICS_API getGeometry(const std::string &expression);

}