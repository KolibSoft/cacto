#include <SFML/Graphics/Transformable.hpp>
#include <Cacto/Graphics/TransformableChains.hpp>

namespace cacto
{

    TransformableChains &TransformableChains::move(const sf::Vector2f &offset)
    {
        asTransformable().move(offset);
        return *this;
    }

    TransformableChains &TransformableChains::scale(const sf::Vector2f &factors)
    {
        asTransformable().scale(factors);
        return *this;
    }

    TransformableChains &TransformableChains::rotate(const sf::Angle &angle)
    {
        asTransformable().rotate(angle);
        return *this;
    }

}