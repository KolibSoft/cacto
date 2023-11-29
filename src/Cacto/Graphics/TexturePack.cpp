#include <fstream>
#include <SFML/Graphics/Texture.hpp>
#include <Cacto/Graphics/TexturePack.hpp>

namespace cacto
{

    const std::filesystem::path &TexturePack::getPath() const
    {
        return m_path;
    }

    void TexturePack::setPath(const std::filesystem::path &value)
    {
        m_path = value;
    }

    const std::string *const TexturePack::getKey(const sf::Texture *const value) const
    {
        for (auto &pair : m_map)
            if (pair.second == value)
                return &pair.first;
        return nullptr;
    }

    const sf::Texture &TexturePack::getTexture(const std::string &key, bool refresh) const
    {
        auto &texture = m_map[key];
        if (texture == nullptr)
            refresh = texture = new sf::Texture();
        if (refresh)
            auto _ = texture->loadFromFile(m_path / key);
        return *texture;
    }

    void TexturePack::setTexture(const std::string &key, const sf::Texture &value, bool refresh)
    {
        auto &texture = m_map[key];
        if (texture == nullptr)
            refresh = texture = new sf::Texture();
        if (refresh)
            auto _ = value.copyToImage().saveToFile(m_path / key);
        *texture = value;
    }

    void TexturePack::refreshToFiles() const
    {
        for (auto &pair : m_map)
            if (pair.second)
                auto _ = pair.second->copyToImage().saveToFile(m_path / pair.first);
    }

    void TexturePack::refreshFromFiles()
    {
        for (auto &pair : m_map)
            if (pair.second)
                auto _ = pair.second->loadFromFile(m_path / pair.first);
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

    const std::string *const getKey(const sf::Texture *const value)
    {
        if (TexturePacks.size() == 0)
            throw std::runtime_error("There are not texture packs");
        for (auto &pair : TexturePacks)
        {
            auto key = pair.second.getKey(value);
            if (key)
                return key;
        }
        return nullptr;
    }

    const sf::Texture &getTexture(const std::string &key)
    {
        if (TexturePacks.size() == 0)
            throw std::runtime_error("There are not texture packs");
        const sf::Texture *texture = nullptr;
        for (auto &pair : TexturePacks)
        {
            texture = &pair.second.getTexture(key);
            if (texture->getSize() != sf::Vector2u{0, 0})
                break;
        }
        return *texture;
    }

    std::unordered_map<std::string, TexturePack> TexturePacks{};

}