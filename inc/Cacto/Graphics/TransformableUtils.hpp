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
    void CACTO_GRAPHICS_API fromXml(sf::Transform &transform, const XmlValue &xml);

    XmlValue CACTO_GRAPHICS_API toXml(const sf::Transformable &transformable);
    void CACTO_GRAPHICS_API fromXml(sf::Transformable &transformable, const XmlValue &xml);

}