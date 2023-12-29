#pragma once

#include <unordered_map>
#include <filesystem>
#include <Cacto/Core/Pack.hpp>
#include <Cacto/Core/Export.hpp>

namespace cacto
{

    class JsonValue;

    template class CACTO_CORE_API Pack<JsonValue>;

    class CACTO_CORE_API JsonPack
        : public virtual Pack<JsonValue>
    {

    public:
        const std::filesystem::path &getPath() const;

        const std::string &getId(const JsonValue &value) const override;
        const JsonValue *const getResource(const std::string &id) const override;

        JsonPack(const std::filesystem::path &path);
        virtual ~JsonPack();

        JsonPack(const JsonPack &other) = delete;
        JsonPack &operator=(const JsonPack &other) = delete;

        JsonPack(JsonPack &&other);
        JsonPack &operator=(JsonPack &&other);

    private:
        std::filesystem::path m_path;
        mutable std::unordered_map<std::string, std::shared_ptr<JsonValue>> m_map;
    };

    const std::string &CACTO_CORE_API getId(const JsonValue &json);
    const JsonValue *const CACTO_CORE_API getJson(const std::string &id);

}
