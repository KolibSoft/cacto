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

    XmlValue CACTO_GRAPHICS_API toXml(const Geometry *const &geometry);
    void CACTO_GRAPHICS_API fromXml(Geometry *&geometry, const XmlValue &xml);

    namespace geometry
    {

        class CACTO_GRAPHICS_API XmlConverter
            : public virtual line::XmlConverter,
              public virtual cacto::XmlConverter<Geometry>
        {

        public:
            XmlValue toXml(const Line *const value) const override;

            XmlConverter() = default;
            virtual ~XmlConverter() = default;
        };

    }

}
