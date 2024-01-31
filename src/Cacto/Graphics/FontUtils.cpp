#include <SFML/Graphics/Font.hpp>
#include <Cacto/Graphics/FontPack.hpp>
#include <Cacto/Graphics/FontUtils.hpp>

namespace cacto
{

    std::string getExpression(const sf::Font *font)
    {
        if (font)
        {
            auto id = getId(*font);
            if (id != "")
            {
                auto expression = "@font/" + id;
                return std::move(expression);
            }
        }
        return "";
    }

    const sf::Font *getFont(const std::string &expression)
    {
        if (expression.compare(0, 6, "@font/") == 0)
        {
            auto id = expression.substr(6);
            auto font = getResource<sf::Font>(id);
            return font;
        }
        return nullptr;
    }

}