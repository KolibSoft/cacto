#ifndef CACTO_LANG_UTILS_HPP
#define CACTO_LANG_UTILS_HPP

#include <string>
#include <vector>
#include <filesystem>
#include <Cacto/Lang/Export.hpp>

namespace cacto
{

    void CACTO_LANG_API replace(std::string &string, const std::string &oldStr, const std::string &newStr);
    std::vector<std::string> CACTO_LANG_API split(const std::string &str, char delimiter);

    void CACTO_LANG_API toFile(const std::string &string, const std::filesystem::path &path);
    void CACTO_LANG_API fromFile(std::string &string, const std::filesystem::path &path);

    template <typename T>
    std::string toString(const T &value) = delete;

    template <typename T>
    void fromString(T &value, const std::string &string) = delete;

    template <typename T>
    void toStringFile(const T &value, const std::filesystem::path &path);

    template <typename T>
    void fromStringFile(T &value, const std::filesystem::path &path);

}

#include <Cacto/Lang/Utils.inl>

#endif