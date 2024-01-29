#include <sstream>
#include <Cacto/Lang/Printer.hpp>
#include <Cacto/Lang/Scanner.hpp>
#include <Cacto/Core/AnglePrinter.hpp>
#include <Cacto/Core/AngleScanner.hpp>
#include <Cacto/Core/AngleUtils.hpp>

namespace cacto
{

    std::string toString(const sf::Angle &angle)
    {
        std::stringstream stream{};
        stream << angle;
        return stream.str();
    }

    sf::Angle toAngle(const std::string &string)
    {
        sf::Angle angle{};
        std::stringstream stream{string};
        stream >> angle;
        return angle;
    }

    std::ostream &operator<<(std::ostream &stream, const sf::Angle &angle)
    {
        Printer printer{stream};
        AnglePrinter tprinter{printer};
        tprinter.printAngle(angle);
        return stream;
    }

    std::istream &operator>>(std::istream &stream, sf::Angle &angle)
    {
        Scanner scanner{stream};
        AngleScanner tscanner{scanner};
        tscanner.scanAngle(angle);
        return stream;
    }

}