#pragma once

#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class Transformable;
}

namespace cacto
{

    class XmlValue;

    XmlValue CACTO_GRAPHICS_API toXml(const sf::Transformable &transformable);
    sf::Transformable CACTO_GRAPHICS_API toTransformable(const XmlValue &xml);

}