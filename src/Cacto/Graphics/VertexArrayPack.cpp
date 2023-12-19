#include <fstream>
#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Graphics/VertexArrayPack.hpp>

namespace cacto
{

    const std::string &VertexArrayPack::getId(const Shared<const sf::VertexArray> &value) const
    {
        for (auto &pair : m_map)
            if (pair.second == value)
                return pair.first;
        return NoId;
    }

    Shared<const sf::VertexArray> VertexArrayPack::getResource(const std::string &id) const
    {
        for (auto &pair : m_map)
            if (pair.first == id)
                return pair.second;
        auto path = m_path / id;
        if (std::filesystem::exists(path))
        {
            auto array = std::make_shared<sf::VertexArray>();
            JsonValue json = nullptr;
            json.fromFile(path);
            fromJson(*array, json);
            m_map.insert({id, array});
            return array;
        }
        else
        {
            m_map.insert({id, nullptr});
            return nullptr;
        }
    }

    void VertexArrayPack::setResource(const std::string &id, const Shared<const sf::VertexArray> &value)
    {
        for (auto &pair : m_map)
            if (pair.first == id)
            {
                pair.second = value;
                return;
            }
        if (value)
        {
            auto path = m_path / id;
            JsonValue json = nullptr;
            json = toJson(*value);
            json.toFile(path);
            m_map.insert({id, value});
        }
        else
        {
            if (std::filesystem::remove(m_path / id))
                m_map.insert({id, nullptr});
        }
    }

    VertexArrayPack::VertexArrayPack(const std::filesystem::path &path)
        : m_path(path),
          m_map()
    {
    }

    VertexArrayPack::~VertexArrayPack() = default;

    const std::string &getId(const Shared<const sf::VertexArray> &array)
    {
        auto &id = Pack<sf::VertexArray>::id(array);
        return id;
    }

    Shared<const sf::VertexArray> getVertexArray(const std::string &id)
    {
        auto array = Pack<sf::VertexArray>::resource(id);
        return std::move(array);
    }

    VertexArrayPack VertexArrays{"."};

}