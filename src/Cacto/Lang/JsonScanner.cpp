#include <Cacto/Lang/JsonScanner.hpp>

namespace cacto
{

    i32t JsonScanner::scanExponent()
    {
        auto cursor = getCursor();
        if (scanClass("Ee", false, 1, 1) && scanClass("+-", true, 1, 1) && scanDigit())
            return getCursor() - cursor;
        setCursor(cursor);
        return 0;
    }

    i32t JsonScanner::scanFraction()
    {
        auto cursor = getCursor();
        if (scanToken(".") && scanDigit())
            return getCursor() - cursor;
        setCursor(cursor);
        return 0;
    }

    i32t JsonScanner::scanNumber()
    {
        auto cursor = getCursor();
        if (scanClass("+-", true, 1, 1) && scanDigit())
        {
            scanFraction();
            scanExponent();
            return getCursor() - cursor;
        }
        setCursor(cursor);
        return 0;
    }

    i32t JsonScanner::scanEscape()
    {
        auto cursor = getCursor();
        if (scanToken("\\") && scanClass("\"\\/bfnrt", false, 1, 1))
            return getCursor() - cursor;
        setCursor(cursor);
        return 0;
    }

    i32t JsonScanner::scanString()
    {
        auto cursor = getCursor();
        if (scanToken("\""))
        {
            while (scanEscape() || scanNotClass("\"\\"))
                continue;
            if (scanToken("\""))
                return getCursor() - cursor;
        }
        setCursor(cursor);
        return 0;
    }

    i32t JsonScanner::scanBoolean()
    {
        auto cursor = getCursor();
        if (scanToken("true") || scanToken("false"))
            return getCursor() - cursor;
        setCursor(cursor);
        return 0;
    }

    i32t JsonScanner::scanNull()
    {
        auto cursor = getCursor();
        if (scanToken("nullptr"))
            return getCursor() - cursor;
        setCursor(cursor);
        return 0;
    }

    JsonScanner::JsonScanner() = default;
    JsonScanner::~JsonScanner() = default;
}