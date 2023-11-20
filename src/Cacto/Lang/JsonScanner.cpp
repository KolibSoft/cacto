#include <Cacto/Lang/JsonScanner.hpp>

namespace cacto
{

    bool JsonScanner::scanExponent()
    {
        auto cursor = getCursor();
        if (scanClass("Ee", false, 1, 1) && scanClass("+-", true, 1, 1) && scanDigit())
            return true;
        setCursor(cursor);
        return false;
    }

    bool JsonScanner::scanFraction()
    {
        auto cursor = getCursor();
        if (scanToken(".") && scanDigit())
            return true;
        setCursor(cursor);
        return false;
    }

    bool JsonScanner::scanNumber()
    {
        auto cursor = getCursor();
        if (scanClass("+-", true, 1, 1) && scanDigit() && option(scanFraction()) && option(scanExponent()))
            return true;
        setCursor(cursor);
        return false;
    }

    bool JsonScanner::scanEscape()
    {
        auto cursor = getCursor();
        if (scanToken("\\") && scanClass("\"\\/bfnrt", false, 1, 1))
            return true;
        setCursor(cursor);
        return false;
    }

    bool JsonScanner::scanString()
    {
        auto cursor = getCursor();
        if (scanToken("\""))
        {
            while (scanEscape() || scanNotClass("\"\\"))
                continue;
            if (scanToken("\""))
                return true;
        }
        setCursor(cursor);
        return false;
    }

    bool JsonScanner::scanBoolean()
    {
        auto cursor = getCursor();
        if (scanToken("true") || scanToken("false"))
            return true;
        setCursor(cursor);
        return false;
    }

    bool JsonScanner::scanNull()
    {
        auto cursor = getCursor();
        if (scanToken("null"))
            return true;
        setCursor(cursor);
        return false;
    }

    JsonScanner::JsonScanner() = default;
    JsonScanner::~JsonScanner() = default;
}