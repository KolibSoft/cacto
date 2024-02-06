#pragma once

#include <utility>
#include <Cacto/Graphics/TransformableChains.hpp>

namespace cacto
{

    inline TransformableChains &&TransformableChains::spawn(const sf::Vector2f &origin) &&
    {
        return std::move(spawn(origin));
    }

    inline TransformableChains &&TransformableChains::locate(const sf::Vector2f &position) &&
    {
        return std::move(locate(position));
    }

    inline TransformableChains &&TransformableChains::resize(const sf::Vector2f &factors) &&
    {
        return std::move(resize(factors));
    }

    inline TransformableChains &&TransformableChains::direction(const sf::Angle &angle) &&
    {
        return std::move(direction(angle));
    }

    inline TransformableChains &&TransformableChains::move(const sf::Vector2f &offset) &&
    {
        return std::move(move(offset));
    }

    inline TransformableChains &&TransformableChains::rotate(const sf::Angle &angle) &&
    {
        return std::move(rotate(angle));
    }

}