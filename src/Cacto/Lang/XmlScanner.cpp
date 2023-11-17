#include <stdexcept>
#include <Cacto/Lang/XmlScanner.hpp>

namespace cacto
{

    i32t XmlScanner::scanEscape()
    {
        auto eScan = [&]
        {
            return scanToken("&");
        };
        auto cScan = [&]
        {
            return scanGroup({[&]
                              { return scanToken("lt"); },
                              [&]
                              { return scanToken("gt"); },
                              [&]
                              { return scanToken("amp"); },
                              [&]
                              { return scanToken("quot"); },
                              [&]
                              { return scanToken("apos"); }});
        };
        auto dScan = [&]
        {
            return scanToken(";");
        };
        auto index = scanSequence({eScan, cScan, dScan});
        return index;
    }

    i32t XmlScanner::scanText()
    {
        auto eScan = [&]
        {
            return scanOption([&]
                              { return scanEscape(); });
        };
        auto cScan = [&]
        {
            return scanOption([&]
                              { return scanNot([&]
                                               { return scanClass("&<>\"'\n"); }); });
        };
        auto index = scanWhile([&]
                               { return scanGroup({eScan, cScan}); });
        return index;
    }

    i32t XmlScanner::scanXmlIdentifier()
    {
        auto under = [&]
        {
            return scanToken("_");
        };
        auto word = [&]
        {
            return scanWord();
        };
        auto digit = [&]
        {
            return scanDigit();
        };
        auto specials = [&]
        {
            return scanClass(":-.");
        };
        auto index = scanSequence({[&]
                                   {
                                       return scanGroup({under, word});
                                   },
                                   [&]
                                   {
                                       return scanOption([&]
                                                         { return scanWhile([&]
                                                                            { return scanGroup({under, word, digit, specials}); }); });
                                   }});
        auto deny = std::string(":-.");
        while (deny.find(available(-1)) != std::string::npos)
        {
            index -= 1;
            setCursor(getCursor() - 1);
        }
        return index;
    }

    i32t XmlScanner::scanName()
    {
        return scanXmlIdentifier();
    }

    i32t XmlScanner::scanAttribute()
    {
        return scanXmlIdentifier();
    }

    i32t XmlScanner::scanValue()
    {
        auto tScan = [&]
        {
            return scanOption([&]
                              { return scanText(); });
        };
        auto qScan = [&]
        {
            return scanToken("\"");
        };
        auto index = scanSequence({qScan, tScan, qScan});
        return index;
    }

    XmlScanner::XmlScanner() = default;
    XmlScanner::~XmlScanner() = default;

}