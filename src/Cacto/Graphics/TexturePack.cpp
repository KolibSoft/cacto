#include <fstream>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <Cacto/Graphics/TexturePack.hpp>

namespace cacto
{

    const std::string &TexturePack::getId(const sf::Texture &value) const
    {
        for (auto &pair : m_map)
            if (pair.second.get() == &value)
                return pair.first;
        return NoId;
    }

    Shared<const sf::Texture> TexturePack::getResource(const std::string &id) const
    {
        for (auto &pair : m_map)
            if (pair.first == id)
                return pair.second;
        auto path = m_path / id;
        if (std::filesystem::exists(path))
        {
            auto texture = std::make_shared<sf::Texture>();
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

    void TexturePack::setResource(const std::string &id, const Shared<const sf::Texture> &value)
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
            auto _ = value->copyToImage().saveToFile(path);
            m_map.insert({id, value});
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

    TexturePack::~TexturePack() = default;

    const std::string &getId(const sf::Texture &texture)
    {
        auto &id = Pack<sf::Texture>::id(texture);
        return id;
    }

    Shared<const sf::Texture> getTexture(const std::string &id)
    {
        auto resource = Pack<sf::Texture>::resource(id);
        return std::move(resource);
    }

    TexturePack Textures{"."};

}