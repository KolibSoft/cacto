#include <SFML/Graphics/Image.hpp>
#include <Cacto/Graphics/ImagePack.hpp>
#include <Cacto/Graphics/ImageUtils.hpp>

namespace cacto
{

    std::string getExpression(const sf::Image *image)
    {
        if (image)
        {
            auto id = getId(*image);
            if (id != "")
            {
                auto expression = "@image/" + id;
                return std::move(expression);
            }
        }
        return "";
    }

    const sf::Image *getImage(const std::string &expression)
    {
        if (expression.compare(0, 7, "@image/") == 0)
        {
            auto id = expression.substr(7);
            auto image = getResource<sf::Image>(id);
            return image;
        }
        return nullptr;
    }

}