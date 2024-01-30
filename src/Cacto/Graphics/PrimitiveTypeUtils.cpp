#include <stdexcept>
#include <Cacto/Graphics/PrimitiveTypeUtils.hpp>

namespace cacto
{

    std::string toString(sf::PrimitiveType primitive)
    {
        if (primitive == sf::PrimitiveType::Points)
            return "Points";
        else if (primitive == sf::PrimitiveType::Lines)
            return "Lines";
        else if (primitive == sf::PrimitiveType::LineStrip)
            return "LineStrip";
        else if (primitive == sf::PrimitiveType::Triangles)
            return "Triangles";
        else if (primitive == sf::PrimitiveType::TriangleStrip)
            return "TriangleStrip";
        else if (primitive == sf::PrimitiveType::TriangleFan)
            return "TriangleFan";
        else
            throw std::runtime_error("Unsupported primitive type");
    }

    sf::PrimitiveType toPrimitive(const std::string &string)
    {
        if (string == "Points")
            return sf::PrimitiveType::Points;
        else if (string == "Lines")
            return sf::PrimitiveType::Lines;
        else if (string == "LineStrip")
            return sf::PrimitiveType::LineStrip;
        else if (string == "Triangles")
            return sf::PrimitiveType::Triangles;
        else if (string == "TriangleStrip")
            return sf::PrimitiveType::TriangleStrip;
        else if (string == "TriangleFan")
            return sf::PrimitiveType::TriangleFan;
        else
            throw std::runtime_error("Unsupported primitive type");
    }

    std::ostream &operator<<(std::ostream &stream, sf::PrimitiveType primitive)
    {
        auto string = toString(primitive);
        stream << string;
        return stream;
    }

    std::istream &operator>>(std::istream &stream, sf::PrimitiveType &primitive)
    {
        std::string string{};
        stream >> string;
        primitive = toPrimitive(string);
        return stream;
    }

}