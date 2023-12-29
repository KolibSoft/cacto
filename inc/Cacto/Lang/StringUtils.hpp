#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <Cacto/Lang/Export.hpp>

namespace cacto
{

    void CACTO_LANG_API replace(std::string &string, const std::string &oldStr, const std::string &newStr);

    void CACTO_LANG_API toFile(const std::string &string, const std::filesystem::path &path);
    void CACTO_LANG_API fromFile(std::string &string, const std::filesystem::path &path);

}
