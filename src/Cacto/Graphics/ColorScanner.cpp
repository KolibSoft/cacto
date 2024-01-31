#include <sstream>
#include <SFML/Graphics/Color.hpp>
#include <Cacto/Lang/Scanner.hpp>
#include <Cacto/Graphics/ColorScanner.hpp>

namespace cacto
{

    Scanner &ColorScanner::getScanner() const
    {
        return *m_scanner;
    }

    void ColorScanner::setScanner(Scanner &value)
    {
        m_scanner = &value;
    }

    bool ColorScanner::scanColor(u32t &color)
    {
        auto cursor = m_scanner->getCursor();
        if (m_scanner->scanToken("#") && m_scanner->scanClass("1234567890ABCDEFabcdef", false, 8))
        {
            auto token = m_scanner->take();
            char separator = 0;
            std::stringstream stream{token};
            stream >> separator >> std::hex >> color;
            return true;
        }
        m_scanner->setCursor(cursor);
        return false;
    }

    bool ColorScanner::scanColor(sf::Color &color)
    {
        u32t integer = 0;
        if (scanColor(integer))
        {
            color = sf::Color(integer);
            return true;
        }
        return false;
    }

    ColorScanner::ColorScanner(Scanner &scanner)
        : m_scanner(&scanner)
    {
    }

    ColorScanner::~ColorScanner() = default;

}