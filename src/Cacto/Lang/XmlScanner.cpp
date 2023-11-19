#include <stdexcept>
#include <Cacto/Lang/XmlScanner.hpp>

namespace cacto
{

    i32t XmlScanner::scanEscape()
    {
        auto cursor = getCursor();
        if (scanToken("&") && (scanToken("lt") || scanToken("gt") || scanToken("amp") || scanToken("quot") || scanToken("pos")) && scanToken(";"))
            return getCursor() - cursor;
        setCursor(cursor);
        return 0;
    }

    i32t XmlScanner::scanText()
    {
        auto cursor = getCursor();
        while (scanEscape() || scanNotClass("&<>\"'\n"))
            continue;
        return getCursor() - cursor;
    }

    i32t XmlScanner::scanIdentifier()
    {
        auto cursor = getCursor();
        if (scanClass("_") || scanWord())
        {
            while (scanClass("_") || scanWord() || scanDigit() || scanClass(":-."))
                continue;
            discardClass(":-.");
            return getCursor() - cursor;
        }
        setCursor(cursor);
        return 0;
    }

    i32t XmlScanner::scanName()
    {
        return scanIdentifier();
    }

    i32t XmlScanner::scanAttribute()
    {
        return scanIdentifier();
    }

    i32t XmlScanner::scanValue()
    {
        auto cursor = getCursor();
        if (scanClass("\"") && scanText() && scanClass("\""))
            return getCursor() - cursor;
        setCursor(cursor);
        return 0;
    }

    XmlScanner::XmlScanner() = default;
    XmlScanner::~XmlScanner() = default;

}