#pragma once

#include <utility>
#include <Cacto/UI/Surface.hpp>

namespace cacto
{

    inline Surface &&Surface::setGeometry(const Geometry *const value) &&
    {
        return std::move(setGeometry(value));
    }

    inline Surface &&Surface::setPrecision(szt value) &&
    {
        return std::move(setPrecision(value));
    }

    inline Surface &&Surface::setColor(const sf::Color &value) &&
    {
        return std::move(setColor(value));
    }

    inline Surface &&Surface::setTexture(const sf::Texture *const value, bool resetRect) &&
    {
        return std::move(setTexture(value, resetRect));
    }

    inline Surface &&Surface::setTextureRect(const sf::FloatRect &value) &&
    {
        return std::move(setTextureRect(value));
    }

    inline Surface &&Surface::setId(const std::string &value) &&
    {
        return std::move(setId(value));
    }

}