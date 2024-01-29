#include <sstream>
#include <SFML/System/Vector2.hpp>
#include <Cacto/Lang/Printer.hpp>
#include <Cacto/Core/VectorPrinter.hpp>

namespace cacto
{

    Printer &VectorPrinter::getPrinter() const
    {
        return *m_printer;
    }

    void VectorPrinter::setPrinter(Printer &value)
    {
        m_printer = &value;
    }

    void VectorPrinter::printVector(f64t x, f64t y)
    {
        std::stringstream stream{};
        stream << x << "," << y;
        auto components = stream.str();
        m_printer->print(components);
    }

    void VectorPrinter::printVector(const sf::Vector2f &vector)
    {
        printVector(vector.x, vector.y);
    }

    VectorPrinter::VectorPrinter(Printer &printer)
        : m_printer(&printer)
    {
    }

    VectorPrinter::~VectorPrinter() = default;

}