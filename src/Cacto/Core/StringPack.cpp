#include <fstream>
#include <SFML/System/String.hpp>
#include <Cacto/Lang/Utils.hpp>
#include <Cacto/Core/StringPack.hpp>

namespace cacto
{

    const std::filesystem::path &StringPack::getPath() const
    {
        return m_path;
    }

    const std::string &StringPack::getId(const sf::String &value) const
    {
        for (auto &pair : m_map)
            if (*pair.second == value)
                return pair.first;
        return NoId;
    }

    const sf::String *const StringPack::getResource(const std::string &id) const
    {
        for (auto &pair : m_map)
            if (pair.first == id)
                return pair.second.get();
        return nullptr;
    }

    StringPack::StringPack(const std::filesystem::path &path)
        : m_path(path),
          m_map()
    {
        try
        {
            JsonValue json = nullptr;
            json.fromFile(path);
            for (auto &pair : json.asObject())
            {
                auto string = std::make_shared<sf::String>(pair.second.getString(""));
                m_map.insert({pair.first, string});
            }
        }
        catch (...)
        {
        }
    }

    StringPack::~StringPack() = default;

    StringPack::StringPack(StringPack &&other)
        : m_path(std::move(other.m_path)),
          m_map(std::move(other.m_map))
    {
    }

    StringPack &StringPack::operator=(StringPack &&other)
    {
        m_path = std::move(other.m_path);
        m_map = std::move(other.m_map);
        return *this;
    }

    const std::string &getId(const sf::String &string)
    {
        auto &id = Pack<sf::String>::id(string);
        return id;
    }

    const sf::String *const getString(const std::string &id)
    {
        auto string = Pack<sf::String>::resource(id);
        return string;
    }

    std::string toAttribute(const sf::String &string)
    {
        auto &id = getId(string);
        if (id == Pack<sf::String>::NoId)
            return string.toAnsiString();
        return id;
    }

    sf::String fromAttribute(const std::string &id, const sf::String &def)
    {
        auto string = getString(id);
        if (string)
            return *string;
        return def;
    }

}