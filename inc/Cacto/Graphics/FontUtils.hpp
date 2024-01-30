#pragma once

#include <string>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class Font;
}

namespace cacto
{

    std::string CACTO_GRAPHICS_API getExpression(const sf::Font *font);
    const sf::Font *CACTO_GRAPHICS_API getFont(const std::string &expression);

}