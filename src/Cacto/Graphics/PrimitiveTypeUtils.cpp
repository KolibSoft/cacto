#include <Cacto/Graphics/PrimitiveTypeUtils.hpp>

namespace cacto
{

    std::string toString(const sf::PrimitiveType &primitive)
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

    void fromString(sf::PrimitiveType &primitive, const std::string &string)
    {
        if (string == "Points")
            primitive = sf::PrimitiveType::Points;
        else if (string == "Lines")
            primitive = sf::PrimitiveType::Lines;
        else if (string == "LineStrip")
            primitive = sf::PrimitiveType::LineStrip;
        else if (string == "Triangles")
            primitive = sf::PrimitiveType::Triangles;
        else if (string == "TriangleStrip")
            primitive = sf::PrimitiveType::TriangleStrip;
        else if (string == "TriangleFan")
            primitive = sf::PrimitiveType::TriangleFan;
        else
            throw std::runtime_error("Unsupported primitive type");
    }

}