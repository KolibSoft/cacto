#ifndef CACTO_STRAIGHT_HPP
#define CACTO_STRAIGHT_HPP

#include <Cacto/Graphics/Export.hpp>
#include <Cacto/Graphics/Line.hpp>

namespace cacto
{

    class CACTO_GRAPHICS_API Straight final
        : public virtual Line
    {

    public:
        szt getPointCount() const override final;
        sf::Vector2f getPoint(szt index, szt precision = 1) const override final;

        Straight(const sf::Vector2f &begin, const sf::Vector2f &end);
        virtual ~Straight();

    private:
        sf::Vector2f m_begin;
        sf::Vector2f m_end;
    };

}

#endif