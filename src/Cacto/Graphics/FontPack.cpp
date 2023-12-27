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
            if (pair.second.get() == &value)
                return pair.first;
        return NoId;
    }

    const sf::Font *const FontPack::getResource(const std::string &id) const
    {
        for (auto &pair : m_map)
            if (pair.first == id)
                return pair.second.get();
        auto path = m_path / id;
        if (std::filesystem::exists(path))
        {
            auto font = std::make_shared<sf::Font>();
            auto _ = font->loadFromFile(path);
            m_map.insert({id, font});
            return font.get();
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

    FontPack::~FontPack() = default;

    const std::string &getId(const sf::Font &font)
    {
        auto &id = Pack<sf::Font>::id(font);
        return id;
    }

    const sf::Font *const getFont(const std::string &id)
    {
        auto font = Pack<sf::Font>::resource(id);
        return font;
    }

}