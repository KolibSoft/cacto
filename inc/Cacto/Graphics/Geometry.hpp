#pragma once

#include <Cacto/Graphics/Line.hpp>

namespace sf
{

    template <typename T>
    class Rect;

    using FloatRect = Rect<float>;

}

namespace cacto
{

    class Geometry
        : public virtual Line
    {

    public:
        virtual sf::FloatRect getBounds() const = 0;
        virtual bool containsPoint(const sf::Vector2f &point) const = 0;

        Geometry() = default;
        virtual ~Geometry() = default;
    };

    template class CACTO_GRAPHICS_API cacto::XmlConverter<Geometry>;

    XmlValue CACTO_GRAPHICS_API toXml(const Shared<const Geometry> &geometry);
    void CACTO_GRAPHICS_API fromXml(Shared<Geometry> &geometry, const XmlValue &xml);

    namespace geometry
    {

        class CACTO_GRAPHICS_API LineXmlConverter
            : public line::XmlConverter
        {

        public:
            XmlValue toXml(const Shared<const Line> &value) const override;
            Shared<Line> fromXml(const XmlValue &xml) const override;

            LineXmlConverter() = default;
            virtual ~LineXmlConverter() = default;
        };

        extern LineXmlConverter CACTO_GRAPHICS_API LineConverter;

        class CACTO_GRAPHICS_API XmlConverter
            : public cacto::XmlConverter<Geometry>
        {

        public:
            XmlConverter() = default;
            virtual ~XmlConverter() = default;
        };

    }

}
