#ifndef CACTO_BEZIER_HPP
#define CACTO_BEZIER_HPP

#include <vector>
#include <Cacto/Graphics/Export.hpp>
#include <Cacto/Graphics/Line.hpp>

namespace cacto
{

    class CACTO_GRAPHICS_API Bezier final
        : public Line
    {

    public:
        sf::Vector2f getPoint(szt index, szt precision = 1) const override final;
        sf::Vector2f getDirection(szt index, szt precision = 1) const override final;

        Bezier(const std::vector<sf::Vector2f> &points);
        virtual ~Bezier();

    private:
        std::vector<sf::Vector2f> m_points;
    };

}

#endif