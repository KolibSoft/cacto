#include <sstream>
#include <SFML/Graphics/Transformable.hpp>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Core/VectorUtils.hpp>
#include <Cacto/Core/AngleUtils.hpp>
#include <Cacto/Graphics/VectorUtils.hpp>
#include <Cacto/Graphics/TransformableUtils.hpp>

namespace cacto
{

    XmlValue toXml(const sf::Transform &transform)
    {
        auto matrix = transform.getMatrix();
        f32t values[9]{matrix[0], matrix[4], matrix[12],
                       matrix[1], matrix[5], matrix[13],
                       matrix[3], matrix[7], matrix[15]};
        char separator = ',';
        std::stringstream stream{};
        stream << values[0] << separator << values[1] << separator << values[2] << separator << values[3] << separator << values[4] << separator << values[5] << separator << values[6] << separator << values[7] << separator << values[8];
        std::string _matrix{stream.str()};
        XmlValue xml{"Transform", {}};
        xml["matrix"] = _matrix;
        return std::move(xml);
    }

    sf::Transform CACTO_GRAPHICS_API toTransform(const XmlValue &xml)
    {
        sf::Transform transform = {};
        auto matrix = xml.getAttribute("matrix", "1,0,0,0,1,0,0,0,1");
        f32t values[9]{};
        char separator = ',';
        std::stringstream stream{matrix};
        stream >> values[0] >> separator >> values[1] >> separator >> values[2] >> separator >> values[3] >> separator >> values[4] >> separator >> values[5] >> separator >> values[6] >> separator >> values[7] >> separator >> values[8];
        transform = sf::Transform(values[0], values[1], values[2],
                                  values[3], values[4], values[5],
                                  values[6], values[7], values[8]);
        if (xml.isTag())
            for (auto &item : xml.asContent())
                if (item.isTag())
                {
                    if (item.getName() == "Scale")
                    {
                        auto factors = toVector(item.getAttribute("factors", "1,1"));
                        transform.scale(factors);
                    }
                    else if (item.getName() == "Translate")
                    {
                        auto offset = toVector(item.getAttribute("offset", "0,0"));
                        transform.translate(offset);
                    }
                    else if (item.getName() == "Rotate")
                    {
                        auto angle = toAngle(item.getAttribute("angle", "0deg"));
                        transform.rotate(angle);
                    }
                }
        return std::move(transform);
    }

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
            for (auto &item : xml.asContent())
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