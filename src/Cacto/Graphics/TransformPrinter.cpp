#include <sstream>
#include <SFML/Graphics/Transform.hpp>
#include <Cacto/Lang/Printer.hpp>
#include <Cacto/Graphics/TransformPrinter.hpp>

namespace cacto
{

    Printer &TransformPrinter::getPrinter() const
    {
        return *m_printer;
    }

    void TransformPrinter::setPrinter(Printer &value)
    {
        m_printer = &value;
    }

    void TransformPrinter::printTransform(f32t a00, f32t a01, f32t a02, f32t a10, f32t a11, f32t a12, f32t a20, f32t a21, f32t a22)
    {
        std::stringstream stream{};
        char separator = ',';
        stream << a00 << separator << a01 << separator << a02 << separator << a10 << separator << a11 << separator << a12 << separator << a20 << separator << a21 << separator << a22;
        auto string = stream.str();
        m_printer->print(string);
    }

    void TransformPrinter::printTransform(const sf::Transform &transform)
    {
        auto matrix = transform.getMatrix();
        printTransform(matrix[0], matrix[4], matrix[12],
                       matrix[1], matrix[5], matrix[13],
                       matrix[3], matrix[7], matrix[15]);
    }

    TransformPrinter::TransformPrinter(Printer &printer)
        : m_printer(&printer)
    {
    }

    TransformPrinter::~TransformPrinter() = default;

}