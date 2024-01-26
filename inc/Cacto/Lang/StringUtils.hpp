#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <Cacto/Lang/Export.hpp>

namespace cacto
{

    void CACTO_LANG_API replace(std::string &string, const std::string &oldStr, const std::string &newStr);

}
