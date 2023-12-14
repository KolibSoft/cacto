#pragma once

#include <Cacto/Graphics/Geometry.hpp>

namespace cacto
{

    class CACTO_GRAPHICS_API Ellipse final
        : public virtual Geometry
    {

    public:
        szt getPointCount() const override final;
        sf::Vector2f getPoint(szt index, szt precision = 1) const override final;

        sf::FloatRect getBounds() const override final;
        bool containsPoint(const sf::Vector2f &point) const override final;

        const sf::Vector2f getCenter() const;
        void setCenter(const sf::Vector2f &value);

        const sf::Vector2f getDiameters() const;
        void setDiameters(const sf::Vector2f &value);

        Ellipse(const sf::Vector2f &center = {0, 0}, const sf::Vector2f &diameters = {1, 1});
        virtual ~Ellipse();

        static Ellipse Identity;

    private:
        f32t m_centerX;
        f32t m_centerY;
        f32t m_radiusX;
        f32t m_radiusY;

        f32t m_left;
        f32t m_top;
        f32t m_right;
        f32t m_bottom;
    };

    JsonValue CACTO_GRAPHICS_API toJson(const Ellipse &ellipse);
    void CACTO_GRAPHICS_API fromJson(Ellipse &ellipse, const JsonValue &json);

    namespace ellipse
    {

        class CACTO_GRAPHICS_API JsonConverter
            : public virtual geometry::JsonConverter
        {
        public:
            JsonValue toJson(const Geometry *const value) const override;
            Geometry *fromJson(const JsonValue &json) const override;

            JsonConverter() = default;
            virtual ~JsonConverter() = default;
        };

        extern JsonConverter CACTO_GRAPHICS_API Converter;

    }

}
