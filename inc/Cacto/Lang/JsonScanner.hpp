#pragma once

#include <Cacto/Lang/Scanner.hpp>

namespace cacto
{

    class CACTO_LANG_API JsonScanner
        : public Scanner
    {

    public:
        bool scanExponent();
        bool scanFraction();
        bool scanNumber();

        bool scanEscape();
        bool scanString();

        bool scanBoolean();
        bool scanNull();

        JsonScanner(std::istream &stream);
        virtual ~JsonScanner();
    };

}
