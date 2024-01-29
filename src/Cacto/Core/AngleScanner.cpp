#include <sstream>
#include <SFML/System/Angle.hpp>
#include <Cacto/Lang/Scanner.hpp>
#include <Cacto/Core/AngleScanner.hpp>

namespace cacto
{

    Scanner &AngleScanner::getScanner() const
    {
        return *m_scanner;
    }

    void AngleScanner::setScanner(Scanner &value)
    {
        m_scanner = &value;
    }

    bool AngleScanner::scanDegrees(f64t &degrees)
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
        if (m_scanner->scanClass("+-", true, 1) && m_scanner->scanDigit() && m_scanner->option(scanFraction()) && m_scanner->scanToken("deg"))
        {
            auto token = m_scanner->take();
            std::stringstream stream{token};
            stream >> degrees;
            return true;
        }
        m_scanner->setCursor(cursor);
        return false;
    }

    bool AngleScanner::scanRadians(f64t &radians)
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
        if (m_scanner->scanClass("+-", true, 1) && m_scanner->scanDigit() && m_scanner->option(scanFraction()) && m_scanner->scanToken("rad"))
        {
            auto token = m_scanner->take();
            std::stringstream stream{token};
            stream >> radians;
            return true;
        }
        m_scanner->setCursor(cursor);
        return false;
    }

    bool AngleScanner::scanAngle(sf::Angle &angle)
    {
        f64t degrees = 0;
        if (scanDegrees(degrees))
        {
            angle = sf::degrees(degrees);
            return true;
        }

        f64t radians = 0;
        if (scanRadians(radians))
        {
            angle = sf::radians(radians);
            return true;
        }

        return false;
    }

    AngleScanner::AngleScanner(Scanner &scanner)
        : m_scanner(&scanner)
    {
    }

    AngleScanner::~AngleScanner() = default;

}