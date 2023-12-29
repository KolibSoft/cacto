#include <fstream>
#include <SFML/Graphics/Rect.hpp>
#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Graphics/RectUtils.hpp>
#include <Cacto/Graphics/RectPack.hpp>

namespace cacto
{

    const std::filesystem::path &RectPack::getPath() const
    {
        return m_path;
    }

    const std::string &RectPack::getId(const sf::FloatRect &value) const
    {
        for (auto &pair : m_map)
            if (*pair.second == value)
                return pair.first;
        return NoId;
    }

    const sf::FloatRect *const RectPack::getResource(const std::string &id) const
    {
        for (auto &pair : m_map)
            if (pair.first == id)
                return pair.second.get();
        return nullptr;
    }

    RectPack::RectPack(const std::filesystem::path &path)
        : m_path(path),
          m_map()
    {
        try
        {
            JsonValue json = nullptr;
            json.fromFile(path);
            for (auto &pair : json.asObject())
            {
                auto rect = std::make_shared<sf::FloatRect>();
                cacto::fromString(*rect, pair.second.getString("0,0,0,0"));
                m_map.insert({pair.first, rect});
            }
        }
        catch (...)
        {
        }
    }

    RectPack::~RectPack() = default;

    RectPack::RectPack(RectPack &&other)
        : m_path(std::move(other.m_path)),
          m_map(std::move(other.m_map))
    {
    }

    RectPack &RectPack::operator=(RectPack &&other)
    {
        m_path = std::move(other.m_path);
        m_map = std::move(other.m_map);
        return *this;
    }

    const std::string &getId(const sf::FloatRect &string)
    {
        auto &id = Pack<sf::FloatRect>::id(string);
        return id;
    }

    const sf::FloatRect *const getRect(const std::string &id)
    {
        auto rect = Pack<sf::FloatRect>::resource(id);
        return rect;
    }

}