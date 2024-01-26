#include <fstream>
#include <SFML/System/String.hpp>
#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Core/StringPack.hpp>

namespace cacto
{

    const std::filesystem::path &StringPack::getPath() const
    {
        return m_path;
    }

    const std::string &StringPack::getId(const sf::String &value) const
    {
        load();
        for (auto &pair : m_map)
            if (*pair.second == value)
                return pair.first;
        return NoId;
    }

    const sf::String *const StringPack::getResource(const std::string &id) const
    {
        load();
        for (auto &pair : m_map)
            if (pair.first == id)
                return pair.second.get();
        return nullptr;
    }

    StringPack::StringPack(const std::filesystem::path &path)
        : m_path(path),
          m_loaded(),
          m_map()
    {
    }

    StringPack::~StringPack() = default;

    StringPack::StringPack(StringPack &&other)
        : m_path(std::move(other.m_path)),
          m_loaded(other.m_loaded),
          m_map(std::move(other.m_map))
    {
        other.m_loaded = false;
    }

    StringPack &StringPack::operator=(StringPack &&other)
    {
        m_path = std::move(other.m_path);
        m_loaded = other.m_loaded;
        m_map = std::move(other.m_map);
        other.m_loaded = false;
        return *this;
    }

    void StringPack::load() const
    {
        if (!m_loaded)
        {
            try
            {
                JsonValue json = nullptr;
                std::ifstream stream{m_path};
                stream >> json;
                for (auto &pair : json.asObject())
                {
                    auto string = std::make_shared<sf::String>(pair.second.getString(""));
                    m_map.insert({pair.first, string});
                }
            }
            catch (...)
            {
            }
            m_loaded = true;
        }
    }

}