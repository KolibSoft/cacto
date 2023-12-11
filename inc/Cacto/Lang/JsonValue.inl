#include <Cacto/Lang/JsonValue.hpp>

namespace cacto
{

    template <typename T>
    inline void toJsonFile(const T &value, const std::filesystem::path &path, szt identation)
    {
        JsonValue json = toJson<T>(value);
        json.toFile(path, identation);
    }

    template <typename T>
    inline T fromJsonFile(const std::filesystem::path &path)
    {
        JsonValue json = nullptr;
        json.fromFile(path);
        auto value = fromJson<T>(json);
        return std::move(value);
    }

}