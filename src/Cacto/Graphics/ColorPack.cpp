#include <fstream>
#include <SFML/Graphics/Color.hpp>
#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Graphics/ColorUtils.hpp>
#include <Cacto/Graphics/ColorPack.hpp>

namespace cacto
{

    const std::filesystem::path &ColorPack::getPath() const
    {
        return m_path;
    }

    const std::string &ColorPack::getId(const sf::Color &value) const
    {
        load();
        for (auto &pair : m_map)
            if (*pair.second == value)
                return pair.first;
        return NoId;
    }

    const sf::Color *const ColorPack::getResource(const std::string &id) const
    {
        load();
        for (auto &pair : m_map)
            if (pair.first == id)
                return pair.second.get();
        return nullptr;
    }

    ColorPack::ColorPack(const std::filesystem::path &path)
        : m_path(path),
          m_loaded(),
          m_map()
    {
    }

    ColorPack::~ColorPack() = default;

    ColorPack::ColorPack(ColorPack &&other)
        : m_path(std::move(other.m_path)),
          m_loaded(other.m_loaded),
          m_map(std::move(other.m_map))
    {
        other.m_loaded = false;
    }

    ColorPack &ColorPack::operator=(ColorPack &&other)
    {
        m_path = std::move(other.m_path);
        m_loaded = other.m_loaded;
        m_map = std::move(other.m_map);
        other.m_loaded = false;
        return *this;
    }

    void ColorPack::load() const
    {
        if (!m_loaded)
        {
            try
            {
                JsonValue json = nullptr;
                json.fromFile(m_path);
                for (auto &pair : json.asObject())
                {
                    auto color = std::make_shared<sf::Color>();
                    cacto::fromString(*color, pair.second.getString("#00000000"));
                    m_map.insert({pair.first, color});
                }
            }
            catch (...)
            {
            }
            m_loaded = true;
        }
    }

    const std::string &getId(const sf::Color &string)
    {
        auto &id = Pack<sf::Color>::id(string);
        return id;
    }

    const sf::Color *const getColor(const std::string &id)
    {
        auto color = Pack<sf::Color>::resource(id);
        return color;
    }

}