#pragma

#include <stdexcept>
#include <Cacto/Graphics/TextDirection.hpp>

namespace cacto
{

    std::string toString(TextDirection direction)
    {
        if (direction == TextDirection::ToLeft)
            return "ToLeft";
        else if (direction == TextDirection::ToRight)
            return "ToRight";
        else if (direction == TextDirection::ToTop)
            return "ToTop";
        else if (direction == TextDirection::ToBottom)
            return "ToBottom";
        else
            throw std::runtime_error("Invalid direction value");
    }

    TextDirection toDirection(const std::string &string)
    {
        if (string == "ToLeft")
            return TextDirection::ToLeft;
        else if (string == "ToRight")
            return TextDirection::ToRight;
        else if (string == "ToTop")
            return TextDirection::ToTop;
        else if (string == "ToBottom")
            return TextDirection::ToBottom;
        else
            throw std::runtime_error("Invalid direction value");
    }

    std::ostream &operator<<(std::ostream &stream, TextDirection direction)
    {
        auto string = toString(direction);
        stream << string;
        return stream;
    }

    std::istream &operator>>(std::istream &stream, TextDirection &direction)
    {
        std::string string{};
        stream >> string;
        direction = toDirection(string);
        return stream;
    }

}