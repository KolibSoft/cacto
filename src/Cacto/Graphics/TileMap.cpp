#include <SFML/Graphics/RenderTarget.hpp>
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
        for (i32t y = area.top; y < area.height; y++)
            for (i32t x = area.left; x < area.width; x++)
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

}