#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Graphics/RectPack.hpp>
#include <Cacto/Graphics/ColorPack.hpp>
#include <Cacto/Graphics/TexturePack.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Graphics/TileMap.hpp>

namespace cacto
{

    const std::string &TileMap::getId() const
    {
        return m_id;
    }

    TileMap &TileMap::setId(const std::string &value)
    {
        m_id = value;
        return *this;
    }

    const sf::Texture *const TileMap::getTexture() const
    {
        return m_texture;
    }

    TileMap &TileMap::setTexture(const sf::Texture *const value)
    {
        m_texture = value;
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

    const sf::FloatRect &TileMap::getTile(const sf::Vector2i &position) const
    {
        if (m_area.contains(position))
        {
            auto index = (position.y - m_area.top) * m_area.width + (position.x - m_area.left);
            auto &tile = m_tiles[index];
            return tile;
        }
        return NoTile;
    }

    TileMap &TileMap::setTile(const sf::Vector2i &position, const sf::FloatRect &tile)
    {
        if (m_area.contains(position))
        {
            auto index = (position.y - m_area.top) * m_area.width + (position.x - m_area.left);
            m_tiles[index] = tile;
            if (m_texture)
            {
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

    TileMap &TileMap::setTiles(const sf::IntRect &area, const sf::FloatRect &tile)
    {
        for (i32t y = area.top; y < area.top + area.height; y++)
            for (i32t x = area.left; x < area.left + area.width; x++)
                setTile({x, y}, tile);
        return *this;
    }

    TileMap &TileMap::fill(const sf::FloatRect &tile)
    {
        setTiles(m_area, tile);
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

    ParentNode *const TileMap::getParent() const
    {
        return m_parent;
    }

    void TileMap::attach(ParentNode &parent)
    {
        if (m_parent == &parent)
            return;
        if (m_parent != nullptr)
            throw std::runtime_error("This node is already attached to another parent");
        if (parent.hasAncestor(*this))
            throw std::runtime_error("This node is an ancestor");
        m_parent = &parent;
        parent.append(*this);
    }

    void TileMap::detach()
    {
        if (m_parent == nullptr)
            return;
        m_parent->remove(*this);
        m_parent = nullptr;
    }

    void TileMap::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
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
        _states.texture = m_texture;
        _states.transform *= m_transformable.getTransform();
        target.draw(m_array, _states);
    }

    TileMap::TileMap()
        : m_id(),
          m_texture(nullptr),
          m_tileSize(),
          m_area(),
          m_transformable(),
          m_parent(),
          m_invalid(true),
          m_array(sf::PrimitiveType::Triangles)
    {
    }

    TileMap::~TileMap() = default;

    const sf::FloatRect TileMap::NoTile{};

    XmlValue toXml(const TileMap &tileMap)
    {
        auto xml = cacto::toXml(tileMap.asTransformable());
        xml.setName("TileMap");
        auto texture = tileMap.getTexture();
        auto tileSize = tileMap.getTileSize();
        auto area = tileMap.getArea();
        xml["texture"] = texture ? getId(*texture) : "";
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
                tile_xml["tile"] = toAttribute(tile);
                tiles.push_back(std::move(tile_xml));
            }
        content.push_back(std::move(chunk));
        return std::move(xml);
    }

    void fromXml(TileMap &tileMap, const XmlValue &xml)
    {
        cacto::fromXml(tileMap.asTransformable(), xml);
        auto texture = getTexture(xml.getAttribute("texture"));
        sf::Vector2f tileSize{};
        sf::FloatRect area{};
        sf::FloatRect fill{};
        cacto::fromString(tileSize, xml.getAttribute("tileSize", "0,0"));
        cacto::fromString(area, xml.getAttribute("area", "0,0,0,0"));
        cacto::fromString(fill, xml.getAttribute("fill", "0,0,0,0"));
        tileMap.setTexture(texture);
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
                                sf::FloatRect tile{};
                                fromAttribute(tile, tile_xml.getAttribute("tile", "0,0,0,0"));
                                tileMap.setTile({i32t(area.left) + x, i32t(area.top) + y}, tile);
                            }
                    }
                    else if (item.getName() == "Tile")
                    {
                        sf::Vector2f tile_position{};
                        sf::FloatRect tile{};
                        fromAttribute(tile, item.getAttribute("tile", "0,0,0,0"));
                        cacto::fromString(tile_position, item.getAttribute("position", "0,0"));
                        tileMap.setTile(sf::Vector2i(tile_position), tile);
                    }
                    else if (item.getName() == "Tiles")
                    {
                        sf::FloatRect tile_area{};
                        sf::FloatRect tile{};
                        fromAttribute(tile, item.getAttribute("tile", "0,0,0,0"));
                        cacto::fromString(tile_area, item.getAttribute("area", "0,0,0,0"));
                        tileMap.setTiles(sf::IntRect(tile_area), tile);
                    }
                }
            }
        }
    }

}