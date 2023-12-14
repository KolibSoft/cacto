#include <fstream>
#include <SFML/Graphics/Texture.hpp>
#include <Cacto/Graphics/TexturePack.hpp>

namespace cacto
{

    const std::string *const TexturePack::getId(const sf::Texture &value) const
    {
        for (auto &pair : m_map)
            if (pair.second == &value)
                return &pair.first;
        return nullptr;
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

    void TexturePack::setResource(const std::string &id, const sf::Texture *const value)
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
                    pair.second = new sf::Texture(*value);
                }
                return;
            }
        if (value)
        {
            auto path = m_path / id;
            auto texture = new sf::Texture(*value);
            auto _ = texture->copyToImage().saveToFile(path);
            m_map.insert({id, texture});
        }
        else
        {
            if (std::filesystem::remove(m_path / id))
                m_map.insert({id, nullptr});
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
        {
            if (pair.second)
            {
                delete pair.second;
                pair.second = nullptr;
            }
        }
    }

    const std::string *const getId(const sf::Texture &texture)
    {
        auto id = Pack<sf::Texture>::id(texture);
        return id;
    }

    const sf::Texture *const getTexture(const std::string &id)
    {
        auto texture = Pack<sf::Texture>::resource(id);
        return texture;
    }

    TexturePack Textures{"."};

}