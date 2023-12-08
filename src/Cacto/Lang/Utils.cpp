#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Lang/Utils.hpp>

namespace cacto
{

    void replaceAll(std::string &string, const std::string &oldStr, const std::string &newStr)
    {
        szt pos = 0;
        while ((pos = string.find(oldStr, pos)) != std::string::npos)
        {
            string.replace(pos, oldStr.length(), newStr);
            pos += newStr.length();
        }
    }

}