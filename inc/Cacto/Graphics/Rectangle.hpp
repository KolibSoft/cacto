#ifndef CACTO_RECTANGLE_HPP
#define CACTO_RECTANGLE_HPP

#include <Cacto/Graphics/Geometry.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace cacto
{

    class CACTO_GRAPHICS_API Rectangle final
        : public virtual Geometry
    {

    public:
        szt getSideCount() const override final;
        sf::Vector2f getPoint(szt index, szt precision = 1) const override final;

        sf::FloatRect getBounds() const override final;
        bool containsPoint(const sf::Vector2f &point) const override final;

        Rectangle(const sf::Vector2f &position = {0, 0}, const sf::Vector2f &size = {1, 1});
        virtual ~Rectangle();

        static Rectangle Identity;

    private:
        f32t m_width;
        f32t m_height;

        f32t m_left;
        f32t m_top;
        f32t m_right;
        f32t m_bottom;
    };

}

#endif