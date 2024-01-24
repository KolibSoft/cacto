#include <Cacto/Lang/Printer.hpp>
#include <Cacto/Lang/Printable.hpp>

namespace cacto
{

    std::ostream &operator<<(std::ostream &stream, const Printable &printable)
    {
        Printer printer{stream};
        printable.print(printer);
        printer.flush();
        return stream;
    }

}