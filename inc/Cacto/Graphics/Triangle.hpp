#ifndef CACTO_TRIANGLE_HPP
#define CACTO_TRIANGLE_HPP

#include <Cacto/Graphics/Geometry.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace cacto
{

    class CACTO_GRAPHICS_API Triangle final
        : public virtual Geometry
    {

    public:
        szt getSideCount() const override final;
        sf::Vector2f getPoint(szt index, szt precision = 1) const override final;

        sf::FloatRect getBounds() const override final;
        bool containsPoint(const sf::Vector2f &point) const override final;

        Triangle(const sf::Vector2f &pointA, const sf::Vector2f &pointB, const sf::Vector2f &pointC);
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