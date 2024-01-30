#include <SFML/Graphics/Texture.hpp>
#include <Cacto/Graphics/TexturePack.hpp>
#include <Cacto/Graphics/TextureUtils.hpp>

namespace cacto
{

    std::string getExpression(const sf::Texture *texture)
    {
        if (texture)
        {
            auto id = getId(*texture);
            if (id != "")
            {
                auto expression = "@texture/" + id;
                return std::move(expression);
            }
        }
        return "";
    }

    const sf::Texture *getTexture(const std::string &expression)
    {
        if (expression.compare(0, 9, "@texture/") == 0)
        {
            auto id = expression.substr(9);
            auto texture = getResource<sf::Texture>(id);
            return texture;
        }
        return nullptr;
    }

}