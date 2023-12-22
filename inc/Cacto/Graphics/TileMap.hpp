#pragma once

#include <vector>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Core/LeafNode.hpp>
#include <Cacto/Graphics/DrawNode.hpp>

namespace cacto
{

    class TileSet;

    class CACTO_GRAPHICS_API TileMap
        : public virtual LeafNode,
          public virtual DrawNode
    {

    public:
        const TileSet *const getTileSet() const;
        TileMap &setTileSet(const TileSet *const value);

        const sf::Vector2f &getTileSize() const;
        TileMap &setTileSize(const sf::Vector2f &value);

        const sf::IntRect &getArea() const;
        TileMap &setArea(const sf::IntRect &value);

        const std::string &getTile(const sf::Vector2i &position) const;
        TileMap &setTile(const sf::Vector2i &position, const std::string &id);

        TileMap &setTiles(const sf::IntRect &area, const std::string &id);
        TileMap &fill(const std::string &id);

        const sf::Transformable &asTransformable() const;
        sf::Transformable &asTransformable();

        Node *const getParent() const override;

        TileMap();
        virtual ~TileMap();

        TileMap(const TileMap &other) = delete;
        TileMap &operator=(const TileMap &other) = delete;

        TileMap(TileMap &&other) = delete;
        TileMap &operator=(TileMap &&other) = delete;

        static const std::string NoTile;

    protected:
        void onAttach(Node &parent) override;
        void onDetach(Node &parent) override;

        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        const TileSet *m_tileSet;
        sf::Vector2f m_tileSize;
        sf::IntRect m_area;
        std::vector<std::string> m_tiles;
        sf::Transformable m_transformable;
        Node *m_parent;

        mutable bool m_invalid;
        mutable sf::VertexArray m_array;
    };

    XmlValue CACTO_GRAPHICS_API toXml(const TileMap &tilemap);
    void CACTO_GRAPHICS_API fromXml(TileMap &tilemap, const XmlValue &xml);

}
