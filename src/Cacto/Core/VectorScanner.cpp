#include <sstream>
#include <SFML/System/Vector2.hpp>
#include <Cacto/Lang/Scanner.hpp>
#include <Cacto/Core/VectorScanner.hpp>

namespace cacto
{

    Scanner &VectorScanner::getScanner() const
    {
        return *m_scanner;
    }

    void VectorScanner::setScanner(Scanner &value)
    {
        m_scanner = &value;
    }

    bool VectorScanner::scanVector(f64t &x, f64t &y)
    {
        auto scanFraction = [&]()
        {
            auto cursor = m_scanner->getCursor();
            if (m_scanner->scanToken(".") && m_scanner->scanDigit())
                return true;
            m_scanner->setCursor(cursor);
            return false;
        };

        auto cursor = m_scanner->getCursor();
        if (m_scanner->scanClass("+-", true, 1) && m_scanner->scanDigit() && m_scanner->option(scanFraction()) && m_scanner->scanToken(",") && m_scanner->scanClass("+-", true, 1) && m_scanner->scanDigit() && m_scanner->option(scanFraction()))
        {
            auto token = m_scanner->take();
            char separator = 0;
            std::stringstream stream{token};
            stream >> x >> separator >> y;
            return true;
        }
        m_scanner->setCursor(cursor);
        return false;
    }

    bool VectorScanner::scanVector(sf::Vector2f &vector)
    {
        f64t x = 0;
        f64t y = 0;
        if (scanVector(x, y))
        {
            vector = sf::Vector2f(x, y);
            return true;
        }

        return false;
    }

    VectorScanner::VectorScanner(Scanner &scanner)
        : m_scanner(&scanner)
    {
    }

    VectorScanner::~VectorScanner() = default;

}