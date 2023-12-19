#include <fstream>
#include <SFML/System/String.hpp>
#include <Cacto/Lang/Utils.hpp>
#include <Cacto/Core/StringPack.hpp>

namespace cacto
{

    const std::string &StringPack::getId(const Shared<const sf::String> &value) const
    {
        for (auto &pair : m_map)
            if (pair.second == value)
                return pair.first;
        return NoId;
    }

    Shared<const sf::String> StringPack::getResource(const std::string &id) const
    {
        for (auto &pair : m_map)
            if (pair.first == id)
                return pair.second;
        try
        {
            std::string _string{};
            fromFile(_string, m_path / id);
            auto string = std::make_shared<sf::String>(_string);
            m_map.insert({id, string});
            return string;
        }
        catch (...)
        {
            m_map.insert({id, nullptr});
            return nullptr;
        }
    }

    void StringPack::setResource(const std::string &id, const Shared<const sf::String> &value)
    {
        for (auto &pair : m_map)
            if (pair.first == id)
            {
                pair.second = value;
                return;
            }
        if (value)
        {
            try
            {
                auto _string = value->toAnsiString();
                toFile(_string, m_path / id);
                m_map.insert({id, value});
            }
            catch (...)
            {
            }
        }
        else
        {
            if (std::filesystem::remove(m_path / id))
                m_map.insert({id, nullptr});
        }
    }

    StringPack::StringPack(const std::filesystem::path &path)
        : m_path(path),
          m_map()
    {
    }

    StringPack::~StringPack() = default;

    const std::string &getId(const Shared<const sf::String> &string)
    {
        auto &id = Pack<sf::String>::id(string);
        return id;
    }

    Shared<const sf::String> getString(const std::string &id)
    {
        auto string = Pack<sf::String>::resource(id);
        return std::move(string);
    }

    StringPack Strings{"."};

}