#ifndef CACTO_XML_SCANNER_HPP
#define CACTO_XML_SCANNER_HPP

#include <Cacto/Lang/Scanner.hpp>

namespace cacto
{

    class CACTO_LANG_API XmlScanner
        : public Scanner
    {

    public:
        i32t scanEscape();
        i32t scanText();

        i32t scanXmlIdentifier();
        i32t scanName();
        i32t scanAttribute();
        i32t scanValue();

        XmlScanner();
        virtual ~XmlScanner();
    };

}

#endif