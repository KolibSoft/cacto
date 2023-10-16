#ifndef CACTO_GEOMETRY_HPP
#define CACTO_GEOMETRY_HPP

#include <SFML/Graphics/Rect.hpp>
#include <Cacto/Graphics/Line.hpp>

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

}

#endif