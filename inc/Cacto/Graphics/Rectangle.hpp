#pragma once

#include <Cacto/Graphics/Geometry.hpp>

namespace cacto
{

    class CACTO_GRAPHICS_API Rectangle final
        : public virtual Geometry
    {

    public:
        szt getPointCount() const override final;
        sf::Vector2f getPoint(szt index, szt precision = 1) const override final;

        sf::FloatRect getBounds() const override final;
        bool containsPoint(const sf::Vector2f &point) const override final;

        sf::Vector2f getPosition() const;
        void setPosition(const sf::Vector2f &value);

        sf::Vector2f getSize() const;
        void setSize(const sf::Vector2f &value);

        Rectangle(const sf::Vector2f &position = {0, 0}, const sf::Vector2f &size = {1, 1});
        virtual ~Rectangle();

        static const Rectangle Identity;

    private:
        f32t m_width;
        f32t m_height;

        f32t m_left;
        f32t m_top;
        f32t m_right;
        f32t m_bottom;
    };

    XmlValue CACTO_GRAPHICS_API toXml(const Rectangle &rectangle);
    void CACTO_GRAPHICS_API fromXml(Rectangle &rectangle, const XmlValue &xml);

    namespace rectangle
    {

        class CACTO_GRAPHICS_API XmlConverter
            : public geometry::XmlConverter
        {

        public:
            XmlValue toXml(const Geometry *const value) const override;
            Geometry *fromXml(const XmlValue &xml) const override;

            XmlConverter() = default;
            virtual ~XmlConverter() = default;
        };
        
        extern XmlConverter CACTO_GRAPHICS_API Converter;

    }

}
