#ifndef CACTO_XML_SCANNER_HPP
#define CACTO_XML_SCANNER_HPP

#include <Cacto/Lang/Scanner.hpp>

namespace cacto
{

    class CACTO_LANG_API XmlScanner
        : public Scanner
    {

    public:
        XmlScanner();
        virtual ~XmlScanner();
    };

}

#endif