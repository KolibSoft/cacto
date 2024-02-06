#pragma once

#include <utility>
#include <Cacto/Graphics/Mesh.hpp>

namespace cacto
{

    inline Mesh &&Mesh::setTexture(const sf::Texture *value) &&
    {
        return std::move(setTexture(value));
    }

    inline Mesh &&Mesh::setId(const std::string &value) &&
    {
        return std::move(setId(value));
    }

}