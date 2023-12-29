#include <sstream>
#include <SFML/Graphics/Rect.hpp>
#include <Cacto/Graphics/RectPack.hpp>
#include <Cacto/Graphics/RectUtils.hpp>

namespace cacto
{

    bool zoneIn(const sf::FloatRect &rect, const sf::FloatRect &zone)
    {
        auto _rectRight = rect.left + rect.width;
        auto _rectBottom = rect.top + rect.height;

        auto _zoneRight = zone.left + zone.width;
        auto _zoneBottom = zone.top + zone.height;

        auto rectLeft = std::min(rect.left, _rectRight);
        auto rectTop = std::min(rect.top, _rectBottom);
        auto rectRight = std::max(rect.left, _rectRight);
        auto rectBottom = std::max(rect.top, _rectBottom);

        auto zoneLeft = std::min(zone.left, _zoneRight);
        auto zoneTop = std::min(zone.top, _zoneBottom);
        auto zoneRight = std::max(zone.left, _zoneRight);
        auto zoneBottom = std::max(zone.top, _zoneBottom);

        auto result = rectLeft <= zoneLeft && rectTop <= zoneTop && rectRight >= zoneRight && rectBottom >= zoneBottom;
        return result;
    }

    bool zoneWith(const sf::FloatRect &rect, const sf::FloatRect &zone)
    {
        auto _rectRight = rect.left + rect.width;
        auto _rectBottom = rect.top + rect.height;

        auto _zoneRight = zone.left + zone.width;
        auto _zoneBottom = zone.top + zone.height;

        auto rectLeft = std::min(rect.left, _rectRight);
        auto rectTop = std::min(rect.top, _rectBottom);
        auto rectRight = std::max(rect.left, _rectRight);
        auto rectBottom = std::max(rect.top, _rectBottom);

        auto zoneLeft = std::min(zone.left, _zoneRight);
        auto zoneTop = std::min(zone.top, _zoneBottom);
        auto zoneRight = std::max(zone.left, _zoneRight);
        auto zoneBottom = std::max(zone.top, _zoneBottom);

        auto result = rectLeft <= zoneRight && rectTop <= zoneBottom && rectRight >= zoneLeft && rectBottom >= zoneTop;
        return result;
    }

    std::string toString(const sf::FloatRect &rect)
    {
        std::stringstream stream{};
        char separator = ',';
        stream << rect.left << separator << rect.top << separator << rect.width << separator << rect.height;
        return stream.str();
    }

    void fromString(sf::FloatRect &rect, const std::string &string)
    {
        std::stringstream stream{string};
        char separator = ',';
        stream >> rect.left >> separator >> rect.top >> separator >> rect.width >> separator >> rect.height;
    }

    std::string toAttribute(const sf::FloatRect &rect)
    {
        auto &id = getId(rect);
        if (id != "")
            return id;
        return toString(rect);
    }

    void fromAttribute(sf::FloatRect &rect, const std::string &attribute)
    {
        auto value = getRect(attribute);
        if (value)
            rect = *value;
        else
            fromString(rect, attribute);
    }

}