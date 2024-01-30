#include <sstream>
#include <SFML/Graphics/Rect.hpp>
#include <Cacto/Lang/Printer.hpp>
#include <Cacto/Lang/Scanner.hpp>
#include <Cacto/Graphics/RectPrinter.hpp>
#include <Cacto/Graphics/RectScanner.hpp>
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
        stream << rect;
        auto string = stream.str();
        return std::move(string);
    }

    sf::FloatRect CACTO_GRAPHICS_API toRect(const std::string &string)
    {
        sf::FloatRect rect{};
        std::stringstream stream{string};
        stream >> rect;
        return std::move(rect);
    }

    std::ostream &operator<<(std::ostream &stream, const sf::FloatRect &rect)
    {
        Printer printer{stream};
        RectPrinter rprinter{printer};
        rprinter.printRect(rect);
        return stream;
    }

    std::istream &operator>>(std::istream &stream, sf::FloatRect &rect)
    {
        Scanner scanner{stream};
        RectScanner rscanner{scanner};
        rscanner.scanRect(rect);
        return stream;
    }

    std::string getExpression(const sf::FloatRect &rect)
    {
        auto id = getId(rect);
        if (id != "")
        {
            auto expression = "@rect/" + id;
            return std::move(expression);
        }
        auto expression = toString(rect);
        return std::move(expression);
    }

    sf::FloatRect getRect(const std::string &expression)
    {
        if (expression.compare(0, 6, "@rect/") == 0)
        {
            auto id = expression.substr(8);
            auto rect = getResource<sf::FloatRect>(id);
            if (rect)
                return *rect;
        }
        auto rect = toRect(expression);
        return std::move(rect);
    }

}