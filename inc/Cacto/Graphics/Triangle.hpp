#ifndef CACTO_TRIANGLE_HPP
#define CACTO_TRIANGLE_HPP

#include <Cacto/Lang/Json.hpp>
#include <Cacto/Graphics/Geometry.hpp>

namespace cacto
{

    class CACTO_GRAPHICS_API Triangle final
        : public virtual Geometry,
          public virtual Json
    {

    public:
        szt getPointCount() const override final;
        sf::Vector2f getPoint(szt index, szt precision = 1) const override final;

        sf::FloatRect getBounds() const override final;
        bool containsPoint(const sf::Vector2f &point) const override final;

        JsonValue toJson() const override;
        void fromJson(const JsonValue &json) override;

        Triangle(const sf::Vector2f &pointA = {0, 0}, const sf::Vector2f &pointB = {0, 0}, const sf::Vector2f &pointC = {0, 0});
        Triangle();
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

}

#endif