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

    JsonScanner::JsonScanner() = default;
    JsonScanner::~JsonScanner() = default;

}