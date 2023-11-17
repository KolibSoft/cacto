#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/Lang/JsonValue.hpp>
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

    std::unordered_map<std::string, sf::FloatRect> tileSetFromFile(const std::filesystem::path &path)
    {
        JsonValue json = nullptr;
        json.fromFile(path);
        sf::Vector2f size{f32t(json["size"][0].asNumber()), f32t(json["size"][1].asNumber())};
        std::unordered_map<std::string, sf::FloatRect> tiles{};
        for (auto &entry : json["tiles"].asObject())
        {
            sf::Vector2i position{i32t(entry.second[0].asNumber()), i32t(entry.second[1].asNumber())};
            auto tile = TileMap::createTile(position, size);
            tiles[entry.first] = tile;
        }
        return tiles;
    }

    TileMap tileMapFromFile(const std::filesystem::path &path)
    {
        JsonValue json = nullptr;
        json.fromFile(path);
        auto tileSet = tileSetFromFile(json["tileSet"].asString());
        sf::Vector2f size{f32t(json["size"][0].asNumber()), f32t(json["size"][1].asNumber())};
        sf::IntRect area{{i32t(json["area"][0].asNumber()), i32t(json["area"][1].asNumber())}, {i32t(json["area"][2].asNumber()), i32t(json["area"][3].asNumber())}};
        auto fill = tileSet[json["fill"].asString()];
        TileMap tileMap{};
        tileMap.setTileSize(size);
        tileMap.setArea(area);
        tileMap.fill(fill);
        for (auto &item : json["tiles"].asArray())
        {
            sf::IntRect tArea{{i32t(item["area"][0].asNumber()), i32t(item["area"][1].asNumber())}, {i32t(item["area"][2].asNumber()), i32t(item["area"][3].asNumber())}};
            auto tile = tileSet[item["tile"].asString()];
            tileMap.setTiles(tArea, tile);
        }
        return tileMap;
    }

}