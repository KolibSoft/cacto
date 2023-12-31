#pragma once

#include <vector>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Core/Node.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class Texture;
}

namespace cacto
{

    class CACTO_GRAPHICS_API TileMap
        : public sf::Transformable,
          public virtual sf::Drawable,
          public virtual ChildNode
    {

    public:
        const std::string &getId() const override;
        TileMap &setId(const std::string &value);

        const sf::Texture *const getTexture() const;
        TileMap &setTexture(const sf::Texture *const value);

        const sf::Vector2f &getTileSize() const;
        TileMap &setTileSize(const sf::Vector2f &value);

        const sf::IntRect &getArea() const;
        TileMap &setArea(const sf::IntRect &value);

        const sf::FloatRect &getTile(const sf::Vector2i &position) const;
        TileMap &setTile(const sf::Vector2i &position, const sf::FloatRect &tile);

        TileMap &setTiles(const sf::IntRect &area, const sf::FloatRect &tile);
        TileMap &fill(const sf::FloatRect &tile);

        ParentNode *const getParent() const override;

        void attach(ParentNode &parent) override;
        void detach() override;

        TileMap();
        virtual ~TileMap();

        TileMap(const TileMap &other) = delete;
        TileMap &operator=(const TileMap &other) = delete;

        TileMap(TileMap &&other) = delete;
        TileMap &operator=(TileMap &&other) = delete;

        static const sf::FloatRect NoTile;

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        std::string m_id;
        const sf::Texture *m_texture;
        sf::Vector2f m_tileSize;
        sf::IntRect m_area;
        std::vector<sf::FloatRect> m_tiles;
        ParentNode *m_parent;

        mutable bool m_invalid;
        mutable sf::VertexArray m_array;
    };

    XmlValue CACTO_GRAPHICS_API toXml(const TileMap &tilemap);
    void CACTO_GRAPHICS_API fromXml(TileMap &tilemap, const XmlValue &xml);

}
