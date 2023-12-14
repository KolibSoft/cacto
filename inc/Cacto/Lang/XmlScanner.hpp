#pragma once

#include <Cacto/Lang/Scanner.hpp>

namespace cacto
{

    class CACTO_LANG_API XmlScanner
        : public Scanner
    {

    public:
        i32t scanEscape();
        i32t scanText();

        i32t scanIdentifier();
        i32t scanName();
        i32t scanAttribute();
        i32t scanValue();

        XmlScanner(std::istream &stream);
        virtual ~XmlScanner();
    };

}
