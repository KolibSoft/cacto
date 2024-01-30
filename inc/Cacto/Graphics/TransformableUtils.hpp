#pragma once

#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class Transform;
    class Transformable;
}

namespace cacto
{

    class XmlValue;

    XmlValue CACTO_GRAPHICS_API toXml(const sf::Transform &transform);
    sf::Transform CACTO_GRAPHICS_API toTransform(const XmlValue &xml);

    XmlValue CACTO_GRAPHICS_API toXml(const sf::Transformable &transformable);
    sf::Transformable CACTO_GRAPHICS_API toTransformable(const XmlValue &xml);

}