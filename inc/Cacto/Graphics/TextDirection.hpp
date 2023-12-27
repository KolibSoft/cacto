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
    void CACTO_GRAPHICS_API fromString(TextDirection &direction, const std::string &string);

}