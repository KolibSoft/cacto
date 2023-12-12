#ifndef CACTO_TRIANGLE_HPP
#define CACTO_TRIANGLE_HPP

#include <Cacto/Graphics/Geometry.hpp>

namespace cacto
{

    class CACTO_GRAPHICS_API Triangle final
        : public virtual Geometry
    {

    public:
        szt getPointCount() const override final;
        sf::Vector2f getPoint(szt index, szt precision = 1) const override final;

        sf::FloatRect getBounds() const override final;
        bool containsPoint(const sf::Vector2f &point) const override final;

        const sf::Vector2f &getPointA() const;
        void setPointA(const sf::Vector2f &value);

        const sf::Vector2f &getPointB() const;
        void setPointB(const sf::Vector2f &value);

        const sf::Vector2f &getPointC() const;
        void setPointC(const sf::Vector2f &value);

        Triangle(const sf::Vector2f &pointA = {0, 0}, const sf::Vector2f &pointB = {0, 0}, const sf::Vector2f &pointC = {0, 0});
        virtual ~Triangle();

    private:
        sf::Vector2f m_pointA;
        sf::Vector2f m_pointB;
        sf::Vector2f m_pointC;

        f32t m_left;
        f32t m_top;
        f32t m_right;
        f32t m_bottom;
    };

    namespace triangle
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

#endif