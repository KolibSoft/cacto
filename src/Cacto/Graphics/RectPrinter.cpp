#include <sstream>
#include <SFML/Graphics/Rect.hpp>
#include <Cacto/Lang/Printer.hpp>
#include <Cacto/Graphics/RectPrinter.hpp>

namespace cacto
{

    Printer &RectPrinter::getPrinter() const
    {
        return *m_printer;
    }

    void RectPrinter::setPrinter(Printer &value)
    {
        m_printer = &value;
    }

    void RectPrinter::printRect(f64t left, f64t top, f64t width, f64t height)
    {
        std::stringstream stream{};
        auto separator = ",";
        stream << left << separator << top << separator << width << separator << height;
        auto string = stream.str();
        m_printer->print(string);
    }

    void RectPrinter::printRect(const sf::FloatRect &rect)
    {
        printRect(rect.left, rect.top, rect.width, rect.height);
    }

    RectPrinter::RectPrinter(Printer &printer)
        : m_printer(&printer)
    {
    }

    RectPrinter::~RectPrinter() = default;

}