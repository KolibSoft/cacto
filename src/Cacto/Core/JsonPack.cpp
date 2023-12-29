#include <fstream>
#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Core/JsonPack.hpp>

namespace cacto
{

    const std::filesystem::path &JsonPack::getPath() const
    {
        return m_path;
    }

    const std::string &JsonPack::getId(const JsonValue &value) const
    {
        for (auto &pair : m_map)
            if (*pair.second == value)
                return pair.first;
        return NoId;
    }

    const JsonValue *const JsonPack::getResource(const std::string &id) const
    {
        for (auto &pair : m_map)
            if (pair.first == id)
                return pair.second.get();
        auto path = m_path / id;
        if (std::filesystem::exists(path))
        {
            auto json = std::make_shared<JsonValue>();
            json->fromFile(path);
            m_map.insert({id, json});
            return json.get();
        }
        else
        {
            m_map.insert({id, nullptr});
            return nullptr;
        }
    }

    JsonPack::JsonPack(const std::filesystem::path &path)
        : m_path(path),
          m_map()
    {
    }

    JsonPack::~JsonPack() = default;

    JsonPack::JsonPack(JsonPack &&other)
        : m_path(std::move(other.m_path)),
          m_map(std::move(other.m_map))
    {
    }

    JsonPack &JsonPack::operator=(JsonPack &&other)
    {
        m_path = std::move(other.m_path);
        m_map = std::move(other.m_map);
        return *this;
    }

    const std::string &getId(const JsonValue &json)
    {
        auto &id = Pack<JsonValue>::id(json);
        return id;
    }

    const JsonValue *const getJson(const std::string &id)
    {
        auto resource = Pack<JsonValue>::resource(id);
        return resource;
    }

}