#pragma once

#include <utility>
#include <Cacto/Graphics/TransformChains.hpp>

namespace cacto
{

    inline TransformChains &&TransformChains::translate(const sf::Vector2f &offset) &&
    {
        return std::move(translate(offset));
    }

    inline TransformChains &&TransformChains::scale(const sf::Vector2f &factors) &&
    {
        return std::move(scale(factors));
    }

    inline TransformChains &&TransformChains::rotate(const sf::Angle &angle) &&
    {
        return std::move(rotate(angle));
    }

    inline TransformChains &&TransformChains::combine(const sf::Transform &transform) &&
    {
        return std::move(combine(transform));
    }

}