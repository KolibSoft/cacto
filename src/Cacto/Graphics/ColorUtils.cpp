#include <sstream>
#include <SFML/Graphics/Color.hpp>
#include <Cacto/Lang/Printer.hpp>
#include <Cacto/Lang/Scanner.hpp>
#include <Cacto/Graphics/ColorPrinter.hpp>
#include <Cacto/Graphics/ColorScanner.hpp>
#include <Cacto/Graphics/ColorPack.hpp>
#include <Cacto/Graphics/ColorUtils.hpp>

namespace cacto
{

    std::string toString(const sf::Color &color)
    {
        std::stringstream stream{};
        stream << color;
        auto string = stream.str();
        return std::move(string);
    }

    sf::Color toColor(const std::string &string)
    {
        sf::Color color{};
        std::stringstream stream{string};
        stream >> color;
        return std::move(color);
    }

    std::ostream &operator<<(std::ostream &stream, const sf::Color &color)
    {
        Printer printer{stream};
        ColorPrinter cprinter{printer};
        cprinter.printColor(color);
        return stream;
    }

    std::istream &operator>>(std::istream &stream, sf::Color &color)
    {
        Scanner scanner{stream};
        ColorScanner cscanner{scanner};
        cscanner.scanColor(color);
        return stream;
    }

    std::string getExpression(const sf::Color &color)
    {
        auto id = getId(color);
        if (id != "")
        {
            auto expression = "@color/" + id;
            return std::move(expression);
        }
        auto expression = toString(color);
        return std::move(expression);
    }

    sf::Color getColor(const std::string &expression)
    {
        if (expression.compare(0, 7, "@color/") == 0)
        {
            auto id = expression.substr(7);
            auto color = getResource<sf::Color>(id);
            if (color)
                return *color;
        }
        auto color = toColor(expression);
        return std::move(color);
    }

}
