#include <Cacto/Lang/Utils.hpp>

namespace cacto
{

    template <typename T>
    inline void toStringFile(const T &value, const std::filesystem::path &path)
    {
        std::string string = toString(value);
        toFile(string, path);
    }

    template <typename T>
    inline void fromStringFile(T &value, const std::filesystem::path &path)
    {
        std::string string{};
        fromFile(string, path);
        fromString(value, string);
    }

}