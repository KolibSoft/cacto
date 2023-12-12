#include <fstream>
#include <SFML/System/String.hpp>
#include <Cacto/Lang/Utils.hpp>
#include <Cacto/Core/StringPack.hpp>

namespace cacto
{

    const std::string *const StringPack::getId(const sf::String &value) const
    {
        for (auto &pair : m_map)
            if (pair.second == &value)
                return &pair.first;
        return nullptr;
    }

    const sf::String *const StringPack::getResource(const std::string &id) const
    {
        for (auto &pair : m_map)
            if (pair.first == id)
                return pair.second;
        try
        {
            std::string _string{};
            fromFile(_string, m_path / id);
            auto string = new sf::String(_string);
            m_map.insert({id, string});
            return string;
        }
        catch (...)
        {
            m_map.insert({id, nullptr});
            return nullptr;
        }
    }

    void StringPack::setResource(const std::string &id, const sf::String *const value)
    {
        for (auto &pair : m_map)
            if (pair.first == id)
            {
                if (pair.second && value)
                {
                    *pair.second = *value;
                }
                else if (pair.second && !value)
                {
                    delete pair.second;
                    pair.second = nullptr;
                }
                else if (!pair.second && value)
                {
                    pair.second = new sf::String(*value);
                }
                return;
            }
        if (value)
        {
            try
            {
                auto _string = value->toAnsiString();
                toFile(_string, m_path / id);
                auto string = new sf::String(*value);
                m_map.insert({id, string});
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

    StringPack::~StringPack()
    {
        for (auto &pair : m_map)
        {
            if (pair.second)
            {
                delete pair.second;
                pair.second = nullptr;
            }
        }
    }



    StringPack Strings{"."};

}