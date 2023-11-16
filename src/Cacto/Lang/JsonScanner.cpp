#include <Cacto/Lang/JsonScanner.hpp>

namespace cacto
{

    i32t JsonScanner::scanExponent()
    {
        auto eScan = [&]
        {
            return scanRange(1, 1, [&]
                             { return scanClass("Ee"); });
        };

        auto sScan = [&]
        {
            return scanOption([&]
                              { return scanRange(1, 1, [&]
                                                 { return scanClass("+-"); }); });
        };

        auto dScan = [&]
        {
            return scanDigit();
        };

        auto index = scanSequence({eScan, sScan, dScan});
        return index;
    }

    i32t JsonScanner::scanNumber()
    {

        auto sScan = [&]
        {
            return scanOption([&]
                              { return scanRange(1, 1, [&]
                                                 { return scanClass("+-"); }); });
        };

        auto dScan = [&]
        {
            return scanDigit();
        };

        auto pScan = [&]
        {
            return scanToken(".");
        };

        auto fScan = [&]
        {
            return scanOption([&]
                              { return scanSequence({pScan, dScan}); });
        };

        auto eScan = [&]
        {
            return scanOption([&]
                              { return scanExponent(); });
        };

        auto index = scanSequence({sScan, dScan, fScan, eScan});
        return index;
    }

    i32t JsonScanner::scanEscape()
    {
        auto eScan = [&]
        {
            return scanToken("\\");
        };
        auto cScan = [&]
        {
            return scanRange(1, 1, [&]
                             { return scanClass("\"\\/bfnrt"); });
        };
        auto index = scanSequence({eScan, cScan});
        return index;
    }

    i32t JsonScanner::scanString()
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
                                               { return scanClass("\"\\"); }); });
        };
        auto sScan = [&]
        {
            return scanOption([&]
                              { return scanWhile([&]
                                                 { return scanGroup({eScan, cScan}); }); });
        };
        auto qScan = [&]
        {
            return scanToken("\"");
        };
        auto index = scanSequence({qScan, sScan, qScan});
        return index;
    }

    i32t JsonScanner::scanBoolean()
    {
        auto index = scanGroup({[&]
                                {
                                    return scanToken("false");
                                },
                                [&]
                                {
                                    return scanToken("true");
                                }});
        return index;
    }

    i32t JsonScanner::scanNull()
    {
        auto index = scanToken("null");
        return index;
    }

    JsonScanner::JsonScanner() = default;
    JsonScanner::~JsonScanner() = default;

}