#include <fstream>
#include <SFML/System/String.hpp>
#include <Cacto/Lang/Utils.hpp>
#include <Cacto/Core/StringPack.hpp>

namespace cacto
{

    const std::string &StringPack::getId(const sf::String &value) const
    {
        for (auto &pair : m_map)
            if (pair.second.get() == &value)
                return pair.first;
        return NoId;
    }

    const sf::String *const StringPack::getResource(const std::string &id) const
    {
        for (auto &pair : m_map)
            if (pair.first == id)
                return pair.second.get();
        try
        {
            std::string _string{};
            fromFile(_string, m_path / id);
            auto string = std::make_shared<sf::String>(_string);
            m_map.insert({id, string});
            return string.get();
        }
        catch (...)
        {
            m_map.insert({id, nullptr});
            return nullptr;
        }
    }

    StringPack::StringPack(const std::filesystem::path &path)
        : m_path(path),
          m_map()
    {
    }

    StringPack::~StringPack() = default;

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

}