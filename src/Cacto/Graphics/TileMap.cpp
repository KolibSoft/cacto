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

    TileMap *TileMap::clone() const
    {
        auto tileMap = new TileMap(*this);
        return tileMap;
    }

    TileMap::TileMap()
        : m_transformable(),
          m_texture(nullptr),
          m_tileSize(),
          m_area(),
          m_tiles(),
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

    TileMap::TileMap(const TileMap &other)
        : m_transformable(other.m_transformable),
          m_texture(other.m_texture),
          m_tileSize(other.m_tileSize),
          m_area(other.m_area),
          m_tiles(other.m_tiles),
          m_id(other.m_id),
          m_parent(),
          m_invalid(other.m_invalid),
          m_array(other.m_array)
    {
    }

    TileMap &TileMap::operator=(const TileMap &other)
    {
        TileMap copy{other};
        *this = std::move(copy);
        return *this;
    }

    TileMap::TileMap(TileMap &&other)
        : TileMap()
    {
        *this = std::move(other);
    }

    TileMap &TileMap::operator=(TileMap &&other)
    {
        m_transformable = std::move(other.m_transformable);
        m_texture = other.m_texture;
        m_tileSize = std::move(other.m_tileSize);
        m_area = std::move(other.m_area);
        m_tiles = std::move(other.m_tiles);
        m_id = std::move(other.m_id);
        m_invalid = other.m_invalid;
        m_array = std::move(other.m_array);
        other.m_texture = nullptr;
        other.m_invalid = true;
        other.detach();
        return *this;
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

    XmlValue toXml(const TileMap &tileMap)
    {
        XmlValue xml{"TileMap", {}};
        xml["id"] = tileMap.getId();
        xml["texture"] = getExpression(tileMap.getTexture());
        xml["tileSize"] = toString(tileMap.getTileSize());
        xml["area"] = toString(sf::FloatRect(tileMap.getArea()));
        auto txml = cacto::toXml(tileMap.asTransformable());
        for (auto &pair : txml.asTag().attributes)
            xml[pair.first] = pair.second;
        auto &content = xml.asTag().content;
        XmlValue chunk{"Chunk", {}};
        auto area{tileMap.getArea()};
        chunk["area"] = toString(sf::FloatRect(area));
        auto &tiles = chunk.asTag().content;
        for (i32t y = 0; y < area.height; y++)
            for (i32t x = 0; x < area.width; x++)
            {
                auto tile = tileMap.getTile({area.left + x, area.top + y});
                XmlValue tile_xml{"Tile", {}};
                tile_xml["tile"] = getExpression(tile);
                tiles.push_back(std::move(tile_xml));
            }
        content.push_back(std::move(chunk));
        return std::move(xml);
    }

    TileMap toTileMap(const XmlValue &xml)
    {
        TileMap tileMap{};
        tileMap.setId(xml.getAttribute("id"));
        tileMap.setTexture(getTexture(xml.getAttribute("texture")));
        tileMap.setTileSize(toVector(xml.getAttribute("tileSize", "0,0")));
        tileMap.setArea(sf::IntRect(toRect(xml.getAttribute("area", "0,0,0,0"))));
        tileMap.fill(getRect(xml.getAttribute("fill", "0,0,0,0")));
        tileMap.asTransformable() = toTransformable(xml);
        if (xml.isTag())
        {
            auto &content = xml.asTag().content;
            for (auto &item : content)
            {
                if (item.isTag())
                {
                    if (item.getName() == "Chunk")
                    {
                        auto area = toRect(item.getAttribute("area", "0,0,0,0"));
                        auto &tiles = item.asTag().content;
                        for (i32t y = 0; y < area.height; y++)
                            for (i32t x = 0; x < area.width; x++)
                            {
                                auto &tile_xml = tiles[y * area.width + x];
                                auto tile = getRect(tile_xml.getAttribute("tile", "0,0,0,0"));
                                tileMap.setTile(tile, {i32t(area.left) + x, i32t(area.top) + y});
                            }
                    }
                    else if (item.getName() == "Tile")
                    {
                        auto tile = getRect(item.getAttribute("tile", "0,0,0,0"));
                        auto tile_position = toVector(item.getAttribute("position", "0,0"));
                        tileMap.setTile(tile, sf::Vector2i(tile_position));
                    }
                    else if (item.getName() == "Tiles")
                    {
                        auto tile = getRect(item.getAttribute("tile", "0,0,0,0"));
                        auto tile_area = toRect(item.getAttribute("tile", "0,0,0,0"));
                        tileMap.setTiles(tile, sf::IntRect(tile_area));
                    }
                }
            }
        }
        return std::move(tileMap);
    }

    namespace tile_map
    {

        XmlValue XmlConverter::toXml(const Node *const value) const
        {
            const TileMap *tileMap = nullptr;
            if (value && typeid(*value) == typeid(TileMap) && (tileMap = dynamic_cast<const TileMap *>(value)))
            {
                auto xml = cacto::toXml(*tileMap);
                return std::move(xml);
            }
            return nullptr;
        }

        Node *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.isTag() && xml.getName() == "TileMap")
            {
                auto tileMap = new TileMap();
                *tileMap = toTileMap(xml);
                return tileMap;
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}