#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Graphics/TileSetPack.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Graphics/TileMap.hpp>

namespace cacto
{

    const TileSet *const TileMap::getTileSet() const
    {
        return m_tileSet;
    }

    TileMap &TileMap::setTileSet(const TileSet *const value)
    {
        m_tileSet = value;
        return *this;
    }

    const sf::Vector2f &TileMap::getTileSize() const
    {
        return m_tileSize;
    }

    TileMap &TileMap::setTileSize(const sf::Vector2f &value)
    {
        m_tileSize = value;
        m_invalid = true;
        return *this;
    }

    const sf::IntRect &TileMap::getArea() const
    {
        return m_area;
    }

    TileMap &TileMap::setArea(const sf::IntRect &value)
    {
        m_area = value;
        m_tiles.resize(value.width * value.height);
        m_array.resize(value.width * value.height * 6);
        m_invalid = true;
        return *this;
    }

    const std::string &TileMap::getTile(const sf::Vector2i &position) const
    {
        if (m_area.contains(position))
        {
            auto index = (position.y - m_area.top) * m_area.width + (position.x - m_area.left);
            auto &tile = m_tiles[index];
            return tile;
        }
        return NoId;
    }

    TileMap &TileMap::setTile(const sf::Vector2i &position, const std::string &id)
    {
        if (m_area.contains(position))
        {
            auto index = (position.y - m_area.top) * m_area.width + (position.x - m_area.left);
            m_tiles[index] = id;
            if (m_tileSet)
            {
                auto tile = m_tileSet->operator[](id);
                auto base = index * 6;
                sf::Vector2f texCoords{tile.left, tile.top};
                m_array[base + 0].texCoords = texCoords;
                texCoords.x += tile.width;
                m_array[base + 1].texCoords = texCoords;
                texCoords.y += tile.height;
                m_array[base + 2].texCoords = texCoords;
                m_array[base + 3].texCoords = texCoords;
                texCoords.x -= tile.width;
                m_array[base + 4].texCoords = texCoords;
                texCoords.y -= tile.height;
                m_array[base + 5].texCoords = texCoords;
            }
        }
        return *this;
    }

    TileMap &TileMap::setTiles(const sf::IntRect &area, const std::string &id)
    {
        for (i32t y = area.top; y < area.top + area.height; y++)
            for (i32t x = area.left; x < area.left + area.width; x++)
                setTile({x, y}, id);
        return *this;
    }

    TileMap &TileMap::fill(const std::string &id)
    {
        setTiles(m_area, id);
        return *this;
    }

    const sf::Transformable &TileMap::asTransformable() const
    {
        return m_transformable;
    }

    sf::Transformable &TileMap::asTransformable()
    {
        return m_transformable;
    }

    Node *const TileMap::getParent() const
    {
        return m_parent;
    }

    TileMap::TileMap()
        : m_tileSet(nullptr),
          m_tileSize(),
          m_area(),
          m_transformable(),
          m_parent(),
          m_invalid(true),
          m_array(sf::PrimitiveType::Triangles)
    {
    }

    TileMap::~TileMap() = default;

    const std::string TileMap::NoTile;

    void TileMap::onAttach(Node &parent)
    {
        m_parent = &parent;
    }

    void TileMap::onDetach(Node &parent)
    {
        m_parent = nullptr;
    }

    void TileMap::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (m_invalid)
        {
            for (i32t y = 0; y < m_area.height; y++)
                for (i32t x = 0; x < m_area.width; x++)
                {
                    sf::Vector2f position{f32t(m_area.left + x) * m_tileSize.x, f32t(m_area.top + y) * m_tileSize.y};
                    auto base = (y * m_area.width + x) * 6;
                    m_array[base + 0].position = position;
                    position.x += m_tileSize.x;
                    m_array[base + 1].position = position;
                    position.y += m_tileSize.y;
                    m_array[base + 2].position = position;
                    m_array[base + 3].position = position;
                    position.x -= m_tileSize.x;
                    m_array[base + 4].position = position;
                    position.y -= m_tileSize.y;
                    m_array[base + 5].position = position;
                }
            m_invalid = false;
        }
        auto _states = states;
        if (m_tileSet == nullptr)
            _states.texture = nullptr;
        else
            _states.texture = m_tileSet->getTexture();
        _states.transform *= m_transformable.getTransform();
        target.draw(m_array, _states);
    }

    XmlValue toXml(const TileMap &tileMap)
    {
        auto xml = cacto::toXml(tileMap.asTransformable());
        xml.setName("TileMap");
        auto tileSet = tileMap.getTileSet();
        auto tileSize = tileMap.getTileSize();
        auto area = tileMap.getArea();
        xml["tileSet"] = tileSet ? getId(*tileSet) : "";
        xml["tileSize"] = toString(tileSize);
        xml["area"] = cacto::toString(sf::FloatRect(area));
        //
        auto &content = xml.asContent();
        XmlValue chunk{"Chunk", {}};
        chunk["area"] = cacto::toString(sf::FloatRect(area));
        auto &tiles = chunk.asContent();
        for (i32t y = 0; y < area.height; y++)
            for (i32t x = 0; x < area.width; x++)
            {
                auto tile = tileMap.getTile({area.left + x, area.top + y});
                XmlValue tile_xml{"Tile", {}};
                tile_xml["tile"] = tile;
                tiles.push_back(std::move(tile_xml));
            }
        content.push_back(std::move(chunk));
        return std::move(xml);
    }

    void fromXml(TileMap &tileMap, const XmlValue &xml)
    {
        cacto::fromXml(tileMap.asTransformable(), xml);
        auto tileSet = getTileSet(xml.getAttribute("tileSet"));
        sf::Vector2f tileSize{};
        sf::FloatRect area{};
        auto fill = xml.getAttribute("fill", "None");
        cacto::fromString(tileSize, xml.getAttribute("tileSize", "0,0"));
        cacto::fromString(area, xml.getAttribute("area", "0,0,0,0"));
        tileMap.setTileSet(tileSet);
        tileMap.setTileSize(tileSize);
        tileMap.setArea(sf::IntRect(area));
        tileMap.fill(fill);
        if (xml.isTag())
        {
            auto &content = xml.asContent();
            for (auto &item : content)
            {
                if (item.isTag())
                {
                    if (item.getName() == "Chunk")
                    {
                        auto &tiles = item.asContent();
                        for (i32t y = 0; y < area.height; y++)
                            for (i32t x = 0; x < area.width; x++)
                            {
                                auto &tile_xml = tiles[y * area.width + x];
                                auto tile = tile_xml.getAttribute("tile", "None");
                                tileMap.setTile({i32t(area.left) + x, i32t(area.top) + y}, tile);
                            }
                    }
                    else if (item.getName() == "Tile")
                    {
                        sf::Vector2f tile_position{};
                        auto tile = item.getAttribute("tile", "None");
                        cacto::fromString(tile_position, item.getAttribute("position", "0,0"));
                        tileMap.setTile(sf::Vector2i(tile_position), tile);
                    }
                    else if (item.getName() == "Tiles")
                    {
                        sf::FloatRect tile_area{};
                        auto tile = item.getAttribute("tile", "None");
                        cacto::fromString(tile_area, item.getAttribute("area", "0,0,0,0"));
                        tileMap.setTiles(sf::IntRect(tile_area), tile);
                    }
                }
            }
        }
    }

}