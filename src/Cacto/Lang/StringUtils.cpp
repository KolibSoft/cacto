#include <fstream>
#include <Cacto/Lang/StringUtils.hpp>

namespace cacto
{

    void replace(std::string &string, const std::string &oldStr, const std::string &newStr)
    {
        szt pos = 0;
        while ((pos = string.find(oldStr, pos)) != std::string::npos)
        {
            string.replace(pos, oldStr.length(), newStr);
            pos += newStr.length();
        }
    }

}