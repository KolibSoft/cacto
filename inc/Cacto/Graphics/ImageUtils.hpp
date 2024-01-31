#pragma once

#include <string>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class Image;
}

namespace cacto
{

    std::string CACTO_GRAPHICS_API getExpression(const sf::Image *image);
    const sf::Image *CACTO_GRAPHICS_API getImage(const std::string &expression);

}