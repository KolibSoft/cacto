#ifndef CACTO_ELLIPSE_HPP
#define CACTO_ELLIPSE_HPP

#include <Cacto/Graphics/Geometry.hpp>
#include <Cacto/Graphics/Export.hpp>

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

        Ellipse(const sf::Vector2f &center, const sf::Vector2f &radius);
        Ellipse();
        ~Ellipse();

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

}

#endif