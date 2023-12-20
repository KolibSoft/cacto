#include <Cacto/Graphics/Geometry.hpp>

namespace cacto
{

    XmlValue toXml(const Shared<const Geometry> &geometry)
    {
        auto xml = XmlConverter<Geometry>::xml(geometry);
        return std::move(xml);
    }

    void fromXml(Shared<Geometry> &geometry, const XmlValue &xml)
    {
        auto value = XmlConverter<Geometry>::value(xml);
        geometry = std::move(value);
    }

    namespace geometry
    {

        XmlValue LineXmlConverter::toXml(const Shared<const Line> &value) const
        {
            try
            {
                auto cast = std::dynamic_pointer_cast<const Geometry>(value);
                auto xml = cacto::XmlConverter<Geometry>::xml(cast);
                return std::move(xml);
            }
            catch (std::bad_cast)
            {
                return nullptr;
            }
        }

        Shared<Line> LineXmlConverter::fromXml(const XmlValue &xml) const
        {
            auto value = cacto::XmlConverter<Geometry>::value(xml);
            return std::move(value);
        }

        LineXmlConverter LineConverter{};

    }

}