#pragma once

#include <string>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class Texture;
}

namespace cacto
{

    std::string CACTO_GRAPHICS_API getExpression(const sf::Texture *texture);
    const sf::Texture *CACTO_GRAPHICS_API getTexture(const std::string &expression);

}