#pragma once

#include <istream>
#include <Cacto/Lang/Export.hpp>

namespace cacto
{

    class Scanner;

    class Scannable
    {

    public:
        virtual bool scan(Scanner &scanner) = 0;

        Scannable() = default;
        virtual ~Scannable() = default;
    };

    std::istream &CACTO_LANG_API operator>>(std::istream &stream, Scannable &scannable);

}