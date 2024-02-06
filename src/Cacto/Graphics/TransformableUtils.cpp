#include <sstream>
#include <SFML/Graphics/Transformable.hpp>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Core/VectorUtils.hpp>
#include <Cacto/Core/AngleUtils.hpp>
#include <Cacto/Graphics/VectorUtils.hpp>
#include <Cacto/Graphics/TransformableUtils.hpp>

namespace cacto
{

    XmlValue toXml(const sf::Transformable &transformable)
    {
        XmlValue xml{"Transformable", {}};
        xml["origin"] = toString(transformable.getOrigin());
        xml["scale"] = toString(transformable.getScale());
        xml["position"] = toString(transformable.getPosition());
        xml["rotation"] = toString(transformable.getRotation());
        return std::move(xml);
    }

    sf::Transformable CACTO_GRAPHICS_API toTransformable(const XmlValue &xml)
    {
        sf::Transformable transformable{};
        auto origin = toVector(xml.getAttribute("origin", "0,0"));
        auto scale = toVector(xml.getAttribute("scale", "1,1"));
        auto position = toVector(xml.getAttribute("position", "0,0"));
        auto rotation = toAngle(xml.getAttribute("rotation", "0deg"));
        transformable.setOrigin(origin);
        transformable.setScale(scale);
        transformable.setPosition(position);
        transformable.setRotation(rotation);
        if (xml.isTag())
            for (auto &item : xml.asTag().content)
                if (item.isTag())
                {
                    if (item.getName() == "Scale")
                    {
                        auto factors = toVector(item.getAttribute("factors", "0,0"));
                        transformable.scale(factors);
                    }
                    else if (item.getName() == "Translate" || item.getName() == "Move")
                    {
                        auto offset = toVector(item.getAttribute("offset", "0,0"));
                        transformable.move(offset);
                    }
                    else if (item.getName() == "Rotate")
                    {
                        auto angle = toAngle(item.getAttribute("angle", "0deg"));
                        transformable.rotate(angle);
                    }
                }
        return std::move(transformable);
    }

}