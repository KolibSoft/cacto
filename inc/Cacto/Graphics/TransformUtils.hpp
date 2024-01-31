#pragma once

#include <string>
#include <ostream>
#include <istream>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class Transform;
}

namespace cacto
{

    class XmlValue;

    std::string CACTO_GRAPHICS_API toString(const sf::Transform &transform);
    sf::Transform CACTO_GRAPHICS_API toTransform(const std::string &string);

    XmlValue CACTO_GRAPHICS_API toXml(const sf::Transform &transform);
    sf::Transform CACTO_GRAPHICS_API toTransform(const XmlValue &xml);

    std::ostream &CACTO_GRAPHICS_API operator<<(std::ostream &stream, const sf::Transform &transform);
    std::istream &CACTO_GRAPHICS_API operator>>(std::istream &stream, sf::Transform &transform);

}