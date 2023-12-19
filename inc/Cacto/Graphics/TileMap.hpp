#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Lang/Object.hpp>
#include <Cacto/Core/LeafNode.hpp>
#include <Cacto/Graphics/DrawNode.hpp>

namespace sf
{
    class Texture;
}

namespace cacto
{

    class CACTO_GRAPHICS_API TileMap
        : public sf::Transformable,
          public Object,
          public virtual LeafNode,
          public virtual DrawNode
    {

    public:
        const Shared<const sf::Texture> &getTexture() const;
        TileMap &setTexture(const Shared<const sf::Texture> &value);

        const sf::Vector2f &getTileSize() const;
        TileMap &setTileSize(const sf::Vector2f &value);

        const sf::IntRect &getArea() const;
        TileMap &setArea(const sf::IntRect &value);

        sf::FloatRect getTile(const sf::Vector2i &position) const;
        TileMap &setTile(const sf::Vector2i &position, const sf::FloatRect &tile);

        TileMap &setTiles(const sf::IntRect &area, const sf::FloatRect &tile);
        TileMap &fill(const sf::FloatRect &tile);

        Shared<Node> getParent() const override;

        TileMap();
        virtual ~TileMap();

        static sf::FloatRect createTile(const sf::Vector2i &position, const sf::Vector2f &size);

    protected:
        void onAttach(const Shared<Node> &parent) override;
        void onDetach(const Shared<Node> &parent) override;

        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        Shared<const sf::Texture> m_texture;
        sf::Vector2f m_tileSize;
        sf::IntRect m_area;
        Weak<Node> m_parent;

        mutable bool m_invalid;
        mutable sf::VertexArray m_array;
    };

    XmlValue CACTO_GRAPHICS_API toXml(const TileMap &tilemap);
    void CACTO_GRAPHICS_API fromXml(TileMap &tilemap, const XmlValue &xml);

}
