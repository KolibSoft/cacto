#ifndef CACTO_TILE_MAP_HPP
#define CACTO_TILE_MAP_HPP

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class Texture;
}

namespace cacto
{

    class CACTO_GRAPHICS_API TileMap
        : public sf::Transformable,
          public virtual sf::Drawable
    {

    public:
        const sf::Texture *const getTexture() const;
        void setTexture(const sf::Texture *const value);

        const sf::Vector2f &getTileSize() const;
        void setTileSize(const sf::Vector2f &value);

        const sf::IntRect &getArea() const;
        void setArea(const sf::IntRect &value);

        void setTile(const sf::Vector2i &position, const sf::FloatRect &tile);
        void setTiles(const sf::IntRect &area, const sf::FloatRect &tile);
        void fill(const sf::FloatRect &tile);

        TileMap();
        virtual ~TileMap();

        static sf::FloatRect createTile(const sf::Vector2i &position, const sf::Vector2f &size);

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        const sf::Texture *m_texture;
        sf::Vector2f m_tileSize;
        sf::IntRect m_area;

        mutable bool m_invalid;
        mutable sf::VertexArray m_array;
    };

}

#endif