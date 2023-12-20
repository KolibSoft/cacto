#pragma once

#include <vector>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Lang/Object.hpp>
#include <Cacto/Core/LeafNode.hpp>
#include <Cacto/Graphics/DrawNode.hpp>

namespace cacto
{

    class TileSet;

    class CACTO_GRAPHICS_API TileMap
        : public sf::Transformable,
          public Object,
          public virtual LeafNode,
          public virtual DrawNode
    {

    public:
        const Shared<const TileSet> &getTileSet() const;
        TileMap &setTileSet(const Shared<const TileSet> &value);

        const sf::Vector2f &getTileSize() const;
        TileMap &setTileSize(const sf::Vector2f &value);

        const sf::IntRect &getArea() const;
        TileMap &setArea(const sf::IntRect &value);

        const std::string &getTile(const sf::Vector2i &position) const;
        TileMap &setTile(const sf::Vector2i &position, const std::string &id);

        TileMap &setTiles(const sf::IntRect &area, const std::string &id);
        TileMap &fill(const std::string &id);

        Shared<Node> getParent() const override;

        TileMap();
        virtual ~TileMap();

        static const std::string NoTile;

    protected:
        void onAttach(const Shared<Node> &parent) override;
        void onDetach(const Shared<Node> &parent) override;

        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        Shared<const TileSet> m_tileSet;
        sf::Vector2f m_tileSize;
        sf::IntRect m_area;
        std::vector<std::string> m_tiles;
        Weak<Node> m_parent;

        mutable bool m_invalid;
        mutable sf::VertexArray m_array;
    };

    XmlValue CACTO_GRAPHICS_API toXml(const TileMap &tilemap);
    void CACTO_GRAPHICS_API fromXml(TileMap &tilemap, const XmlValue &xml);

}
