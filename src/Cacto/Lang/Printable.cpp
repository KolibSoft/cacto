#include <sstream>
#include <fstream>
#include <Cacto/Lang/Printer.hpp>
#include <Cacto/Lang/Printable.hpp>

namespace cacto
{

    std::string Printable::toString() const
    {
        std::stringstream stream{};
        stream << *this;
        auto string = stream.str();
        return std::move(string);
    }

    bool Printable::toFile(const std::filesystem::path &path) const
    {
        try
        {
            std::ofstream stream{path};
            stream << *this;
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    std::ostream &operator<<(std::ostream &stream, const Printable &printable)
    {
        Printer printer{stream};
        printable.print(printer);
        return stream;
    }

}