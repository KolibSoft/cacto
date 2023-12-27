#include <fstream>
#include <Cacto/Lang/Utils.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Graphics/ColorPack.hpp>

namespace cacto
{

    const std::filesystem::path &ColorPack::getPath() const
    {
        return m_path;
    }

    const std::string &ColorPack::getId(const sf::Color &value) const
    {
        for (auto &pair : m_map)
            if (*pair.second == value)
                return pair.first;
        return NoId;
    }

    const sf::Color *const ColorPack::getResource(const std::string &id) const
    {
        for (auto &pair : m_map)
            if (pair.first == id)
                return pair.second.get();
        return nullptr;
    }

    ColorPack::ColorPack(const std::filesystem::path &path)
        : m_path(path),
          m_map()
    {
        try
        {
            JsonValue json = nullptr;
            json.fromFile(path);
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
    }

    ColorPack::~ColorPack() = default;

    ColorPack::ColorPack(ColorPack &&other)
        : m_path(std::move(other.m_path)),
          m_map(std::move(other.m_map))
    {
    }

    ColorPack &ColorPack::operator=(ColorPack &&other)
    {
        m_path = std::move(other.m_path);
        m_map = std::move(other.m_map);
        return *this;
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

    std::string toAttribute(const sf::Color &color)
    {
        auto &id = getId(color);
        if (id == Pack<sf::Color>::NoId)
            return toString(color);
        return id;
    }

    sf::Color fromAttribute(const std::string &id, const sf::Color &def)
    {
        auto color = getColor(id);
        if (color)
            return *color;
        return def;
    }

}