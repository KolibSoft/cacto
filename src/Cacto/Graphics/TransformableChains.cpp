#include <SFML/Graphics/Transformable.hpp>
#include <Cacto/Graphics/TransformableChains.hpp>

namespace cacto
{

    TransformableChains &TransformableChains::spawn(const sf::Vector2f &origin) &
    {
        asTransformable().setOrigin(origin);
        return *this;
    }

    TransformableChains &TransformableChains::place(const sf::Vector2f &position) &
    {
        asTransformable().setPosition(position);
        return *this;
    }

    TransformableChains &TransformableChains::resize(const sf::Vector2f &factors) &
    {
        asTransformable().setScale(factors);
        return *this;
    }

    TransformableChains &TransformableChains::direction(const sf::Angle &angle) &
    {
        asTransformable().setRotation(angle);
        return *this;
    }

    TransformableChains &TransformableChains::move(const sf::Vector2f &offset) &
    {
        asTransformable().move(offset);
        return *this;
    }

    TransformableChains &TransformableChains::scale(const sf::Vector2f &factors) &
    {
        asTransformable().scale(factors);
        return *this;
    }

    TransformableChains &TransformableChains::rotate(const sf::Angle &angle) &
    {
        asTransformable().rotate(angle);
        return *this;
    }

}