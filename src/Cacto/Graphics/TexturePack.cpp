#include <fstream>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <Cacto/Graphics/TexturePack.hpp>

namespace cacto
{

    const std::filesystem::path &TexturePack::getPath() const
    {
        return m_path;
    }

    const std::string &TexturePack::getId(const sf::Texture &value) const
    {
        for (auto &pair : m_map)
            if (pair.second == &value)
                return pair.first;
        return NoId;
    }

    const sf::Texture *const TexturePack::getResource(const std::string &id) const
    {
        for (auto &pair : m_map)
            if (pair.first == id)
                return pair.second;
        auto path = m_path / id;
        if (std::filesystem::exists(path))
        {
            auto texture = new sf::Texture();
            auto _ = texture->loadFromFile(path);
            m_map.insert({id, texture});
            return texture;
        }
        else
        {
            m_map.insert({id, nullptr});
            return nullptr;
        }
    }

    TexturePack::TexturePack(const std::filesystem::path &path)
        : m_path(path),
          m_map()
    {
    }

    TexturePack::~TexturePack()
    {
        for (auto &pair : m_map)
            if (pair.second)
            {
                delete pair.second;
                pair.second = nullptr;
            }
    }

    TexturePack::TexturePack(TexturePack &&other)
        : m_path(std::move(other.m_path)),
          m_map(std::move(other.m_map))
    {
    }

    TexturePack &TexturePack::operator=(TexturePack &&other)
    {
        m_path = std::move(other.m_path);
        m_map = std::move(other.m_map);
        return *this;
    }

}