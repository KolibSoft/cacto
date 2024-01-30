#include <sstream>
#include <SFML/Graphics/Rect.hpp>
#include <Cacto/Lang/Scanner.hpp>
#include <Cacto/Graphics/RectScanner.hpp>

namespace cacto
{

    Scanner &RectScanner::getScanner() const
    {
        return *m_scanner;
    }

    void RectScanner::setScanner(Scanner &value)
    {
        m_scanner = &value;
    }

    bool RectScanner::scanRect(f64t &left, f64t &top, f64t &width, f64t &height)
    {
        auto scanFraction = [&]()
        {
            auto cursor = m_scanner->getCursor();
            if (m_scanner->scanToken(".") && m_scanner->scanDigit())
                return true;
            m_scanner->setCursor(cursor);
            return false;
        };

        auto scanNumber = [&]()
        {
            auto cursor = m_scanner->getCursor();
            if (m_scanner->scanClass("+-", true, 1) && m_scanner->scanDigit() && m_scanner->option(scanFraction()))
                return true;
            m_scanner->setCursor(cursor);
            return false;
        };

        if (scanNumber() && m_scanner->scanToken(",") && scanNumber() && m_scanner->scanToken(",") && scanNumber() && m_scanner->scanToken(",") && scanNumber())
        {
            auto token = m_scanner->take();
            std::stringstream stream{token};
            char separator = 0;
            stream >> left >> separator >> top >> separator >> width >> separator >> height;
            return true;
        }

        return false;
    }

    bool RectScanner::scanRect(sf::FloatRect &rect)
    {
        f64t left = 0;
        f64t top = 0;
        f64t width = 0;
        f64t height = 0;
        if (scanRect(left, top, width, height))
        {
            rect = {{left, top}, {width, height}};
            return true;
        }
        return false;
    }

    RectScanner::RectScanner(Scanner &scanner)
        : m_scanner(&scanner)
    {
    }

    RectScanner::~RectScanner() = default;

}