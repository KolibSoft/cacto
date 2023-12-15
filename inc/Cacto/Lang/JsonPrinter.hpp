#pragma once

#include <Cacto/Lang/Printer.hpp>

namespace cacto
{

    class CACTO_LANG_API JsonPrinter
        : public Printer
    {

    public:
        void printNumber(f64t value);
        void printString(const std::string &value);
        void printBoolean(bool value);
        void printNull();

        JsonPrinter(std::ostream &stream);
        virtual ~JsonPrinter();
    };

}
