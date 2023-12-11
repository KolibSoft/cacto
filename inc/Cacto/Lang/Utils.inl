#include <Cacto/Lang/Utils.hpp>

namespace cacto
{

    template <typename T>
    inline void toStringFile(const T &value, const std::filesystem::path &path)
    {
        auto string = toString<T>(value);
        toFile(string, path);
    }

    template <typename T>
    inline T fromStringFile(const std::filesystem::path &path)
    {
        auto string = fromFile(path);
        auto value = fromString<T>(string);
        return std::move(value);
    }

}