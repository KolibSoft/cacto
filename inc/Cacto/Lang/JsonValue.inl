#include <Cacto/Lang/JsonValue.hpp>

namespace cacto
{

    template <typename T>
    inline void toJsonFile(const T &value, const std::filesystem::path &path, szt identation)
    {
        JsonValue json = toJson(value);
        json.toFile(path, identation);
    }

    template <typename T>
    inline void fromJsonFile(T &value, const std::filesystem::path &path)
    {
        JsonValue json = nullptr;
        json.fromFile(path);
        fromJson(value, json);
    }

}