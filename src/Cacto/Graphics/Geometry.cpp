#include <Cacto/Graphics/Geometry.hpp>

namespace cacto
{

    XmlValue toXml(const Geometry *const &geometry)
    {
        auto xml = XmlConverter<Geometry>::xml(geometry);
        return std::move(xml);
    }

    Geometry *toGeometry(const XmlValue &xml)
    {
        auto value = XmlConverter<Geometry>::value(xml);
        return value;
    }

    namespace geometry
    {

        XmlValue XmlConverter::toXml(const Line *const value) const
        {
            const Geometry *geometry = nullptr;
            if ((geometry = dynamic_cast<const Geometry *>(value)))
            {
                auto xml = cacto::XmlConverter<Geometry>::xml(geometry);
                return std::move(xml);
            }
            return nullptr;
        }

    }

}