#ifndef CACTO_LANG_UTILS_HPP
#define CACTO_LANG_UTILS_HPP

#include <string>
#include <unordered_map>
#include <filesystem>
#include <Cacto/Lang/Export.hpp>

namespace cacto
{

    void CACTO_LANG_API stringMapToFile(const std::filesystem::path &path, const std::unordered_map<std::string, std::string> &map);
    std::unordered_map<std::string, std::string> CACTO_LANG_API stringMapFromFile(const std::filesystem::path &path);

}

#endif