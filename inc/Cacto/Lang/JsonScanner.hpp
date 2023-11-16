#ifndef CACTO_JSON_SCANNER_HPP
#define CACTO_JSON_SCANNER_HPP

#include <Cacto/Lang/Scanner.hpp>

namespace cacto
{

    class CACTO_LANG_API JsonScanner
        : public Scanner
    {

    public:
        i32t scanExponent();
        i32t scanNumber();

        i32t scanEscape();
        i32t scanString();

        JsonScanner();
        virtual ~JsonScanner();
    };

}

#endif