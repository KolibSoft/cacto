#include <sstream>
#include <Cacto/Lang/Printer.hpp>
#include <Cacto/Lang/Scanner.hpp>
#include <Cacto/Core/VectorPrinter.hpp>
#include <Cacto/Core/VectorScanner.hpp>
#include <Cacto/Core/VectorUtils.hpp>

namespace cacto
{

    std::string toString(const sf::Vector2f &vector)
    {
        std::stringstream stream{};
        stream << vector;
        return stream.str();
    }

    sf::Vector2f toVector(const std::string &string)
    {
        sf::Vector2f vector{};
        std::stringstream stream{string};
        stream >> vector;
        return vector;
    }

    std::ostream &operator<<(std::ostream &stream, const sf::Vector2f &vector)
    {
        Printer printer{stream};
        VectorPrinter tprinter{printer};
        tprinter.printVector(vector);
        return stream;
    }

    std::istream &operator>>(std::istream &stream, sf::Vector2f &vector)
    {
        Scanner scanner{stream};
        VectorScanner tscanner{scanner};
        tscanner.scanVector(vector);
        return stream;
    }

}