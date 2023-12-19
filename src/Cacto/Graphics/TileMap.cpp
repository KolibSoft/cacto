#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Graphics/TexturePack.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Graphics/TileMap.hpp>

namespace cacto
{

    const sf::Texture *const TileMap::getTexture() const
    {
        return m_texture;
    }

    void TileMap::setTexture(const sf::Texture *const value)
    {
        m_texture = value;
    }

    const sf::Vector2f &TileMap::getTileSize() const
    {
        return m_tileSize;
    }

    void TileMap::setTileSize(const sf::Vector2f &value)
    {
        m_tileSize = value;
        m_invalid = true;
    }

    const sf::IntRect &TileMap::getArea() const
    {
        return m_area;
    }

    void TileMap::setArea(const sf::IntRect &value)
    {
        m_area = value;
        m_array.resize(value.width * value.height * 6);
        m_invalid = true;
    }

    sf::FloatRect TileMap::getTile(const sf::Vector2i &position) const
    {
        if (m_area.contains(position))
        {
            auto base = ((position.y - m_area.top) * m_area.width + (position.x - m_area.left)) * 6;
            sf::FloatRect tile{m_array[base + 0].texCoords,
                               m_array[base + 2].texCoords - m_array[base + 0].texCoords};
            return tile;
        }
        return {};
    }

    void TileMap::setTile(const sf::Vector2i &position, const sf::FloatRect &tile)
    {
        if (m_area.contains(position))
        {
            auto base = ((position.y - m_area.top) * m_area.width + (position.x - m_area.left)) * 6;
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

    void TileMap::setTiles(const sf::IntRect &area, const sf::FloatRect &tile)
    {
        for (i32t y = area.top; y < area.top + area.height; y++)
            for (i32t x = area.left; x < area.left + area.width; x++)
                setTile({x, y}, tile);
    }

    void TileMap::fill(const sf::FloatRect &tile)
    {
        setTiles(m_area, tile);
    }

    TileMap::TileMap()
        : m_texture(nullptr),
          m_tileSize(),
          m_area(),
          m_invalid(true),
          m_array(sf::PrimitiveType::Triangles)
    {
    }

    TileMap::~TileMap() = default;

    sf::FloatRect TileMap::createTile(const sf::Vector2i &position, const sf::Vector2f &size)
    {
        sf::FloatRect tile{};
        tile.left = f32t(position.x) * size.x;
        tile.top = f32t(position.y) * size.y;
        tile.width = size.x;
        tile.height = size.y;
        return tile;
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
        _states.transform *= getTransform();
        target.draw(m_array, _states);
    }

    JsonValue toJson(const TileMap &tilemap)
    {
        auto json = JsonValue::ObjectValue;
        auto texture = tilemap.getTexture();
        auto tileSize = tilemap.getTileSize();
        auto area = tilemap.getArea();
        if (texture)
        {
            auto id = cacto::getId(*texture);
            json["texture"] = id;
        }
        json["tileSize"] = {tileSize.x, tileSize.y};
        json["area"] = cacto::toJson(sf::FloatRect(area));
        auto &tiles = (json["tiles"] = JsonValue::ArrayValue).asArray();
        for (i32t y = 0; y < area.height; y++)
            for (i32t x = 0; x < area.width; x++)
            {
                auto tile = tilemap.getTile({area.left + x, area.top + y});
                tiles.push_back(cacto::toJson(tile));
            }
        return json;
    }

    void fromJson(TileMap &tilemap, const JsonValue &json)
    {
        auto &texture = json["texture"];
        auto &tileSize = json["tileSize"];
        auto &area = json["area"];
        auto &tiles = json["tiles"];
        if (texture != nullptr)
        {
            auto resource = cacto::getTexture(texture.asString());
            tilemap.setTexture(resource.get());
        }
        tilemap.setTileSize({f32t(tileSize[0].getNumber()), f32t(tileSize[1].getNumber())});
        sf::FloatRect _area{};
        cacto::fromJson(_area, area);
        tilemap.setArea(sf::IntRect(_area));
        for (i32t y = 0; y < _area.height; y++)
            for (i32t x = 0; x < _area.width; x++)
            {
                auto &tile = tiles[y * _area.width + x];
                sf::FloatRect _tile{};
                cacto::fromJson(_tile, tile);
                tilemap.setTile({i32t(_area.left) + x, i32t(_area.top) + y}, _tile);
            }
    }

}