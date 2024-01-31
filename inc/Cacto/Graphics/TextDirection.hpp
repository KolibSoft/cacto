#pragma once

#include <string>
#include <ostream>
#include <istream>
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

    std::ostream &CACTO_GRAPHICS_API operator<<(std::ostream &stream, TextDirection direction);
    std::istream &CACTO_GRAPHICS_API operator>>(std::istream &stream, TextDirection &direction);

}