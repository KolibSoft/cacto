#include <SFML/Graphics/Rect.hpp>
#include <Cacto/Graphics/VectorUtils.hpp>

namespace cacto
{

    sf::Vector2f mapPoint(const sf::Vector2f &point, const sf::FloatRect &bounds, const sf::FloatRect &surface)
    {
        sf::Vector2f result{(point.x - bounds.left) * (surface.width / bounds.width) + surface.left,
                            (point.y - bounds.top) * (surface.height / bounds.height) + surface.top};
        return result;
    }

    sf::Vector2f fitSize(const sf::Vector2f &contentSize, const sf::Vector2f &containerSize)
    {
        sf::Vector2f size{0, 0};
        auto hRatio = contentSize.x / containerSize.x;
        auto vRatio = contentSize.y / containerSize.y;
        if (hRatio < vRatio)
        {
            size.y = containerSize.y;
            size.x = containerSize.y * contentSize.x / contentSize.y;
        }
        else if (vRatio < hRatio)
        {
            size.x = containerSize.x;
            size.y = containerSize.x * contentSize.y / contentSize.x;
        }
        else
        {
            size = containerSize;
        }
        return size;
    }

}