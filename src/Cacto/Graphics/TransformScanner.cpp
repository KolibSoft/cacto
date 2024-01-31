#include <sstream>
#include <SFML/Graphics/Transform.hpp>
#include <Cacto/Lang/Scanner.hpp>
#include <Cacto/Graphics/TransformScanner.hpp>

namespace cacto
{

    Scanner &TransformScanner::getScanner() const
    {
        return *m_scanner;
    }

    void TransformScanner::setScanner(Scanner &value)
    {
        m_scanner = &value;
    }

    bool TransformScanner::scanTransform(f32t &a00, f32t &a01, f32t &a02, f32t &a10, f32t &a11, f32t &a12, f32t &a20, f32t &a21, f32t &a22)
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

        if (scanNumber() && m_scanner->scanToken(",") && scanNumber() && m_scanner->scanToken(",") && scanNumber() && m_scanner->scanToken(",") && scanNumber() && m_scanner->scanToken(",") && scanNumber() && m_scanner->scanToken(",") && scanNumber() && m_scanner->scanToken(",") && scanNumber() && m_scanner->scanToken(",") && scanNumber() && m_scanner->scanToken(",") && scanNumber())
        {
            auto token = m_scanner->take();
            std::stringstream stream{token};
            char separator = 0;
            stream >> a00 >> separator >> a01 >> separator >> a02 >> separator >> a10 >> separator >> a11 >> separator >> a12 >> separator >> a20 >> separator >> a21 >> separator >> a22;
            return true;
        }

        return false;
    }

    bool TransformScanner::scanTransform(sf::Transform &transform)
    {
        f32t a00 = 0;
        f32t a01 = 0;
        f32t a02 = 0;
        f32t a10 = 0;
        f32t a11 = 0;
        f32t a12 = 0;
        f32t a20 = 0;
        f32t a21 = 0;
        f32t a22 = 0;
        if (scanTransform(a00, a01, a02, a10, a11, a12, a20, a21, a22))
        {
            transform = {a00, a01, a02, a10, a11, a12, a20, a21, a22};
            return true;
        }

        return false;
    }

    TransformScanner::TransformScanner(Scanner &scanner)
        : m_scanner(&scanner)
    {
    }

    TransformScanner::~TransformScanner() = default;

}