#include <SFML/Graphics/Transform.hpp>
#include <Cacto/Graphics/TransformChains.hpp>

namespace cacto
{

    TransformChains &TransformChains::translate(const sf::Vector2f &offset)
    {
        asTransform().translate(offset);
        return *this;
    }

    TransformChains &TransformChains::scale(const sf::Vector2f &factors)
    {
        asTransform().scale(factors);
        return *this;
    }

    TransformChains &TransformChains::rotate(const sf::Angle &angle)
    {
        asTransform().rotate(angle);
        return *this;
    }

    TransformChains &TransformChains::combine(const sf::Transform &transform)
    {
        asTransform().combine(transform);
        return *this;
    }

}