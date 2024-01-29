#pragma once

#include <string>
#include <Cacto/Graphics/Export.hpp>

namespace cacto
{

    enum class TextDirection
    {
        ToLeft,
        ToRight,
        ToTop,
        ToBottom
    };

    std::string CACTO_GRAPHICS_API toString(TextDirection direction);
    TextDirection CACTO_GRAPHICS_API toTextDirection(const std::string &string);

}