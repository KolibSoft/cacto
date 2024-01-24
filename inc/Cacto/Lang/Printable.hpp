#pragma once

#include <ostream>
#include <Cacto/Lang/Export.hpp>

namespace cacto
{

    class Printer;

    class Printable
    {
    public:
        virtual void print(Printer &printer) const = 0;

        Printable() = default;
        virtual ~Printable() = default;
    };

    std::ostream &CACTO_LANG_API operator<<(std::ostream &stream, const Printable &printable);

}