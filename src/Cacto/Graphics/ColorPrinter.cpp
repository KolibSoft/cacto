#include <sstream>
#include <iomanip>
#include <SFML/Graphics/Color.hpp>
#include <Cacto/Lang/Printer.hpp>
#include <Cacto/Graphics/ColorPrinter.hpp>

namespace cacto
{

    Printer &ColorPrinter::getPrinter() const
    {
        return *m_printer;
    }

    void ColorPrinter::setPrinter(Printer &value)
    {
        m_printer = &value;
    }

    void ColorPrinter::printColor(u32t color)
    {
        std::stringstream stream{};
        stream << "#" << std::hex << std::setw(8) << std::setfill('0') << std::uppercase << color;
        auto string = stream.str();
        m_printer->print(string);
    }

    void ColorPrinter::printColor(const sf::Color &color)
    {
        auto integer = color.toInteger();
        printColor(integer);
    }

    ColorPrinter::ColorPrinter(Printer &printer)
        : m_printer(&printer)
    {
    }

    ColorPrinter::~ColorPrinter() = default;

}