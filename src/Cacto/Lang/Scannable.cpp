#include <sstream>
#include <fstream>
#include <Cacto/Lang/Scanner.hpp>
#include <Cacto/Lang/Scannable.hpp>

namespace cacto
{

    void Scannable::fromString(const std::string &string)
    {
        std::stringstream stream{string};
        stream >> *this;
    }

    bool Scannable::fromFile(const std::filesystem::path &path)
    {
        try
        {
            std::ifstream stream{path};
            stream >> *this;
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    std::istream &operator>>(std::istream &stream, Scannable &scannable)
    {
        Scanner scanner{stream};
        scannable.scan(scanner);
        return stream;
    }

}