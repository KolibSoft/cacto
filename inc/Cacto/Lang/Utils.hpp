#ifndef CACTO_LANG_UTILS_HPP
#define CACTO_LANG_UTILS_HPP

#include <string>
#include <Cacto/Lang/Export.hpp>

namespace cacto
{

    void CACTO_LANG_API replaceAll(std::string& string, const std::string& oldStr, const std::string& newStr);

}

#endif