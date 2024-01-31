#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Core/ParentNode.hpp>
#include <Cacto/Core/VectorUtils.hpp>
#include <Cacto/Graphics/VectorUtils.hpp>
#include <Cacto/Graphics/RectUtils.hpp>
#include <Cacto/Graphics/TextureUtils.hpp>
#include <Cacto/Graphics/TransformableUtils.hpp>
#include <Cacto/Graphics/TileMap.hpp>

namespace cacto
{

    const sf::Transformable &TileMap::asTransformable() const
    {
        return m_transformable;
    }

    sf::Transformable &TileMap::asTransformable()
    {
        return m_transformable;
    }

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

    TileMap &TileMap::setTile(const sf::FloatRect &tile, const sf::Vector2i &position)
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

    TileMap &TileMap::setTiles(const sf::FloatRect &tile, const sf::IntRect &area)
    {
        for (i32t y = area.top; y < area.top + area.height; y++)
            for (i32t x = area.left; x < area.left + area.width; x++)
                setTile(tile, {x, y});
        return *this;
    }

    TileMap &TileMap::fill(const sf::FloatRect &tile)
    {
        setTiles(tile, m_area);
        return *this;
    }

    Node *const TileMap::getParent() const
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

    XmlValue TileMap::toXml() const
    {
        XmlValue xml{"TileMap", {}};
        xml["id"] = getId();
        xml["texture"] = getExpression(m_texture);
        xml["tileSize"] = toString(m_tileSize);
        xml["area"] = toString(sf::FloatRect(m_area));
        auto txml = cacto::toXml(m_transformable);
        for (auto &pair : txml.asAttributes())
            xml[pair.first] = pair.second;
        auto &content = xml.asContent();
        XmlValue chunk{"Chunk", {}};
        chunk["area"] = toString(sf::FloatRect(m_area));
        auto &tiles = chunk.asContent();
        for (i32t y = 0; y < m_area.height; y++)
            for (i32t x = 0; x < m_area.width; x++)
            {
                auto tile = getTile({m_area.left + x, m_area.top + y});
                XmlValue tile_xml{"Tile", {}};
                tile_xml["tile"] = getExpression(tile);
                tiles.push_back(std::move(tile_xml));
            }
        content.push_back(std::move(chunk));
        return std::move(xml);
    }

    void TileMap::fromXml(const XmlValue &xml)
    {
        m_id = xml.getAttribute("id");
        m_texture = cacto::getTexture(xml.getAttribute("texture"));
        m_tileSize = toVector(xml.getAttribute("tileSize", "0,0"));
        m_area = sf::IntRect(toRect(xml.getAttribute("area", "0,0,0,0")));
        m_tiles.resize(m_area.width * m_area.height);
        m_array.resize(m_area.width * m_area.height * 6);
        m_invalid = true;
        auto frect = getRect(xml.getAttribute("fill", "0,0,0,0"));
        fill(frect);
        m_transformable = toTransformable(xml);
        if (xml.isTag())
        {
            auto &content = xml.asContent();
            for (auto &item : content)
            {
                if (item.isTag())
                {
                    if (item.getName() == "Chunk")
                    {
                        auto area = toRect(item.getAttribute("area", "0,0,0,0"));
                        auto &tiles = item.asContent();
                        for (i32t y = 0; y < area.height; y++)
                            for (i32t x = 0; x < area.width; x++)
                            {
                                auto &tile_xml = tiles[y * area.width + x];
                                auto tile = getRect(tile_xml.getAttribute("tile", "0,0,0,0"));
                                setTile(tile, {i32t(area.left) + x, i32t(area.top) + y});
                            }
                    }
                    else if (item.getName() == "Tile")
                    {
                        auto tile = getRect(item.getAttribute("tile", "0,0,0,0"));
                        auto tile_position = toVector(item.getAttribute("position", "0,0"));
                        setTile(tile, sf::Vector2i(tile_position));
                    }
                    else if (item.getName() == "Tiles")
                    {
                        auto tile = getRect(item.getAttribute("tile", "0,0,0,0"));
                        auto tile_area = toRect(item.getAttribute("tile", "0,0,0,0"));
                        setTiles(tile, sf::IntRect(tile_area));
                    }
                }
            }
        }
    }

    TileMap::TileMap()
        : m_transformable(),
          m_texture(nullptr),
          m_tileSize(),
          m_area(),
          m_id(),
          m_parent(),
          m_invalid(true),
          m_array(sf::PrimitiveType::Triangles)
    {
    }

    TileMap::~TileMap()
    {
        detach();
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

    const sf::FloatRect TileMap::NoTile{};

    namespace tile_map
    {

        XmlValue XmlConverter::toXml(const Node *const value) const
        {
            const TileMap *tileMap = nullptr;
            if (value && typeid(*value) == typeid(TileMap) && (tileMap = dynamic_cast<const TileMap *>(value)))
            {
                auto xml = tileMap->toXml();
                return std::move(xml);
            }
            return nullptr;
        }

        Node *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.isTag() && xml.getName() == "TileMap")
            {
                auto tileMap = new TileMap();
                tileMap->fromXml(xml);
                return tileMap;
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}