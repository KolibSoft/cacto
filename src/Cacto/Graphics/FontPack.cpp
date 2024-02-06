#include <fstream>
#include <SFML/Graphics/Font.hpp>
#include <Cacto/Graphics/FontPack.hpp>

namespace cacto
{

    const std::filesystem::path &FontPack::getPath() const
    {
        return m_path;
    }

    const std::string &FontPack::getId(const sf::Font &value) const
    {
        for (auto &pair : m_map)
            if (pair.second == &value)
                return pair.first;
        return NoId;
    }

    const sf::Font *const FontPack::getResource(const std::string &id) const
    {
        for (auto &pair : m_map)
            if (pair.first == id)
                return pair.second;
        auto path = m_path / id;
        if (std::filesystem::exists(path))
        {
            auto font = new sf::Font();
            auto _ = font->loadFromFile(path);
            m_map.insert({id, font});
            return font;
        }
        else
        {
            m_map.insert({id, nullptr});
            return nullptr;
        }
    }

    FontPack::FontPack(const std::filesystem::path &path)
        : m_path(path),
          m_map()
    {
    }

    FontPack::~FontPack()
    {
        for (auto &pair : m_map)
            if (pair.second)
            {
                delete pair.second;
                pair.second = nullptr;
            }
    }

    FontPack::FontPack(FontPack &&other)
        : m_path(std::move(other.m_path)),
          m_map(std::move(other.m_map))
    {
    }

    FontPack &FontPack::operator=(FontPack &&other)
    {
        m_path = std::move(other.m_path);
        m_map = std::move(other.m_map);
        return *this;
    }

}