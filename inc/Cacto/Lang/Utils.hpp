#ifndef CACTO_LANG_UTILS_HPP
#define CACTO_LANG_UTILS_HPP

#include <string>
#include <vector>
#include <Cacto/Lang/Export.hpp>

namespace cacto
{

    void CACTO_LANG_API replace(std::string& string, const std::string& oldStr, const std::string& newStr);
    std::vector<std::string> CACTO_LANG_API split(const std::string &str, char delimiter);

}

#endif