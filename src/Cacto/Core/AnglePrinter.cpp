#include <sstream>
#include <SFML/System/Angle.hpp>
#include <Cacto/Lang/Printer.hpp>
#include <Cacto/Core/AnglePrinter.hpp>

namespace cacto
{

    Printer &AnglePrinter::getPrinter() const
    {
        return *m_printer;
    }

    void AnglePrinter::setPrinter(Printer &value)
    {
        m_printer = &value;
    }

    void AnglePrinter::printDegrees(f64t degrees)
    {
        std::stringstream stream{};
        stream << degrees;
        auto number = stream.str();
        m_printer->print(number);
        m_printer->print("deg");
    }

    void AnglePrinter::printRadians(f64t radians)
    {
        std::stringstream stream{};
        stream << radians;
        auto number = stream.str();
        m_printer->print(number);
        m_printer->print("rad");
    }

    void AnglePrinter::printAngle(const sf::Angle &angle)
    {
        auto degrees = angle.asDegrees();
        printDegrees(degrees);
    }

    AnglePrinter::AnglePrinter(Printer &printer)
        : m_printer(&printer)
    {
    }

    AnglePrinter::~AnglePrinter() = default;

}