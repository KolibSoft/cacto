#include <fstream>
#include <SFML/Graphics/Font.hpp>
#include <Cacto/Graphics/FontPack.hpp>

namespace cacto
{

    const std::string &FontPack::getId(const Shared<const sf::Font> &value) const
    {
        for (auto &pair : m_map)
            if (pair.second == value)
                return pair.first;
        return NoId;
    }

    Shared<const sf::Font> FontPack::getResource(const std::string &id) const
    {
        for (auto &pair : m_map)
            if (pair.first == id)
                return pair.second;
        auto path = m_path / id;
        if (std::filesystem::exists(path))
        {
            auto font = std::make_shared<sf::Font>();
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

    void FontPack::setResource(const std::string &id, const Shared<const sf::Font> &value)
    {
        throw std::runtime_error("Fonts can not be saved nor overwritten");
    }

    FontPack::FontPack(const std::filesystem::path &path)
        : m_path(path),
          m_map()
    {
    }

    FontPack::~FontPack() = default;

    const std::string &getId(const Shared<const sf::Font> &font)
    {
        auto &id = Pack<sf::Font>::id(font);
        return id;
    }

    Shared<const sf::Font> getFont(const std::string &id)
    {
        auto font = Pack<sf::Font>::resource(id);
        return std::move(font);
    }

}