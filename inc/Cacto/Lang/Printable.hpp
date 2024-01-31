#pragma once

#include <string>
#include <ostream>
#include <filesystem>
#include <Cacto/Lang/Export.hpp>

namespace cacto
{

    class Printer;

    class CACTO_LANG_API Printable
    {
    public:
        virtual void print(Printer &printer) const = 0;
        std::string toString() const;
        bool toFile(const std::filesystem::path &path) const;

        Printable() = default;
        virtual ~Printable() = default;
    };

    std::ostream &CACTO_LANG_API operator<<(std::ostream &stream, const Printable &printable);

}