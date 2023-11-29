#include <fstream>
#include <SFML/System/String.hpp>
#include <Cacto/Core/StringPack.hpp>

namespace cacto
{

    const std::filesystem::path &StringPack::getPath() const
    {
        return m_path;
    }

    void StringPack::setPath(const std::filesystem::path &value)
    {
        m_path = value;
    }

    const std::string *const StringPack::getKey(const sf::String *const value) const
    {
        for (auto &pair : m_map)
            if (pair.second == value)
                return &pair.first;
        return nullptr;
    }

    const sf::String &StringPack::getString(const std::string &key, bool refresh) const
    {
        auto &string = m_map[key];
        if (string == nullptr)
            refresh = string = new sf::String();
        if (refresh)
        {
            std::ifstream stream{m_path / key};
            if (stream.is_open())
            {
                std::string _string{std::istreambuf_iterator<c8t>(stream), std::istreambuf_iterator<c8t>()};
                *string = _string;
            }
        }
        return *string;
    }

    void StringPack::setString(const std::string &key, const sf::String &value, bool refresh)
    {
        auto &string = m_map[key];
        if (string == nullptr)
            refresh = string = new sf::String();
        if (refresh)
        {
            std::ofstream stream{m_path / key};
            if (stream.is_open())
            {
                auto _string = value.toAnsiString();
                stream << _string;
            }
        }
        *string = value;
    }

    void StringPack::refreshToFiles() const
    {
        for (auto &pair : m_map)
            if (pair.second)
            {
                std::ofstream stream{m_path / pair.first};
                if (stream.is_open())
                {
                    auto _string = pair.second->toAnsiString();
                    stream << _string;
                }
            }
    }

    void StringPack::refreshFromFiles()
    {
        for (auto &pair : m_map)
            if (pair.second)
            {
                std::ifstream stream{m_path / pair.first};
                if (stream.is_open())
                {
                    std::string _string{std::istreambuf_iterator<c8t>(stream), std::istreambuf_iterator<c8t>()};
                    *pair.second = _string;
                }
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

}