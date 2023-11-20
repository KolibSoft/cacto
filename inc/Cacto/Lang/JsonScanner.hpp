#ifndef CACTO_JSON_SCANNER_HPP
#define CACTO_JSON_SCANNER_HPP

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

        JsonScanner();
        virtual ~JsonScanner();
    };

}

#endif