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

    void toFile(const std::string &string, const std::filesystem::path &path)
    {
        std::ofstream stream{path};
        if (!stream.is_open())
            throw std::runtime_error("Can not open the file");
        stream << string;
    }

    void fromFile(std::string &string, const std::filesystem::path &path)
    {
        std::ifstream stream{path};
        if (!stream.is_open())
            throw std::runtime_error("Can not open the file");
        string = {std::istreambuf_iterator<c8t>(stream), std::istreambuf_iterator<c8t>()};
    }

}