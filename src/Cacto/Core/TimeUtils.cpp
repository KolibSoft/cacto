#include <sstream>
#include <SFML/System/Time.hpp>
#include <Cacto/Lang/Printer.hpp>
#include <Cacto/Lang/Scanner.hpp>
#include <Cacto/Core/TimePrinter.hpp>
#include <Cacto/Core/TimeScanner.hpp>
#include <Cacto/Core/TimeUtils.hpp>

namespace cacto
{

    std::string toString(const sf::Time &time)
    {
        std::stringstream stream{};
        stream << time;
        return stream.str();
    }

    sf::Time toTime(const std::string &string)
    {
        sf::Time time{};
        std::stringstream stream{string};
        stream >> time;
        return time;
    }

    std::ostream &operator<<(std::ostream &stream, const sf::Time &time)
    {
        Printer printer{stream};
        TimePrinter tprinter{printer};
        tprinter.printTime(time);
        return stream;
    }

    std::istream &operator>>(std::istream &stream, sf::Time &time)
    {
        Scanner scanner{stream};
        TimeScanner tscanner{scanner};
        tscanner.scanTime(time);
        return stream;
    }

}