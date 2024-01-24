#include <Cacto/Lang/Scanner.hpp>
#include <Cacto/Lang/Scannable.hpp>

namespace cacto
{

    std::istream &operator>>(std::istream &stream, Scannable &scannable)
    {
        Scanner scanner{stream};
        scannable.scan(scanner);
        return stream;
    }

}