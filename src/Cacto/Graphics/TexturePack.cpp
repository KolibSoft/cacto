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

    const sf::Texture &TexturePack::getTexture(const std::string &key, bool refresh) const
    {
        auto &image = m_map[key];
        if (image == nullptr)
            refresh = image = new sf::Texture();
        if (refresh)
            auto _ = image->loadFromFile(m_path / key);
        return *image;
    }

    void TexturePack::setTexture(const std::string &key, const sf::Texture &value, bool refresh)
    {
        auto &image = m_map[key];
        if (image == nullptr)
            refresh = image = new sf::Texture();
        if (refresh)
            auto _ = value.copyToImage().saveToFile(m_path / key);
        *image = value;
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

}