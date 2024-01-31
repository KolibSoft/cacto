#pragma once

#include <string>
#include <istream>
#include <filesystem>
#include <Cacto/Lang/Export.hpp>

namespace cacto
{

    class Scanner;

    class CACTO_LANG_API Scannable
    {

    public:
        virtual bool scan(Scanner &scanner) = 0;
        void fromString(const std::string &string);
        bool fromFile(const std::filesystem::path &path);

        Scannable() = default;
        virtual ~Scannable() = default;
    };

    std::istream &CACTO_LANG_API operator>>(std::istream &stream, Scannable &scannable);

}