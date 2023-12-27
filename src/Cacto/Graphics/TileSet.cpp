#include <SFML/Graphics/Rect.hpp>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Graphics/TexturePack.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Graphics/TileSet.hpp>

namespace cacto
{

    const sf::Texture *const TileSet::getTexture() const
    {
        return m_texture;
    }

    TileSet &TileSet::setTexture(const sf::Texture *const value)
    {
        m_texture = value;
        return *this;
    }

    const std::map<std::string, sf::FloatRect> &TileSet::asMap() const
    {
        return m_map;
    }

    std::map<std::string, sf::FloatRect> &TileSet::asMap()
    {
        return m_map;
    }

    const sf::FloatRect &TileSet::operator[](const std::string &id) const
    {
        return m_map[id];
    }

    sf::FloatRect &TileSet::operator[](const std::string &id)
    {
        return m_map[id];
    }

    TileSet::TileSet()
        : m_texture(),
          m_map()
    {
    }

    TileSet::~TileSet() = default;

    XmlValue toXml(const TileSet &tileSet)
    {
        XmlValue xml{"TileSet", {}};
        auto texture = tileSet.getTexture();
        xml["texture"] = texture ? getId(*texture) : "";
        auto &content = xml.asContent();
        for (auto &pair : tileSet.asMap())
        {
            XmlValue tile_xml{"Tile", {}};
            tile_xml["id"] = pair.first;
            tile_xml["rect"] = cacto::toString(pair.second);
            content.push_back(std::move(tile_xml));
        }
        return std::move(xml);
    }

    void fromXml(TileSet &tileSet, const XmlValue &xml)
    {
        tileSet = {};
        auto texture = getTexture(xml.getAttribute("texture"));
        tileSet.setTexture(texture);
        if (xml.isTag())
        {
            auto &map = tileSet.asMap();
            for (auto &tile_xml : xml.asContent())
            {
                auto id = tile_xml.getAttribute("id");
                sf::FloatRect tile{};
                cacto::fromString(tile, tile_xml.getAttribute("rect", "0,0,0,0"));
                map.insert({id, tile});
            }
        }
    }

}