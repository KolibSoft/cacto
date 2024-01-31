#pragma once

#include <vector>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Lang/XmlConverter.hpp>
#include <Cacto/Core/ChildNode.hpp>
#include <Cacto/Graphics/TransformableChains.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class Texture;
}

namespace cacto
{

    class CACTO_GRAPHICS_API TileMap
        : public virtual sf::Drawable,
          public virtual TransformableChains,
          public virtual ChildNode
    {

    public:
        const sf::Transformable &asTransformable() const;
        sf::Transformable &asTransformable() override;

        const std::string &getId() const override;
        TileMap &setId(const std::string &value);

        const sf::Texture *const getTexture() const;
        TileMap &setTexture(const sf::Texture *const value);

        const sf::Vector2f &getTileSize() const;
        TileMap &setTileSize(const sf::Vector2f &value);

        const sf::IntRect &getArea() const;
        TileMap &setArea(const sf::IntRect &value);

        const sf::FloatRect &getTile(const sf::Vector2i &position) const;
        TileMap &setTile(const sf::FloatRect &tile, const sf::Vector2i &position);

        TileMap &setTiles(const sf::FloatRect &tile, const sf::IntRect &area);
        TileMap &fill(const sf::FloatRect &tile);

        Node *const getParent() const override;

        void attach(ParentNode &parent) override;
        void detach() override;

        XmlValue toXml() const;
        void fromXml(const XmlValue &xml);

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
        sf::Transformable m_transformable;
        const sf::Texture *m_texture;
        sf::Vector2f m_tileSize;
        sf::IntRect m_area;
        std::vector<sf::FloatRect> m_tiles;
        std::string m_id;
        ParentNode *m_parent;

        mutable bool m_invalid;
        mutable sf::VertexArray m_array;
    };

    namespace tile_map
    {

        class XmlConverter
            : public virtual cacto::XmlConverter<Node>
        {

        public:
            XmlValue toXml(const Node *const value) const override;
            Node *fromXml(const XmlValue &xml) const override;

            XmlConverter() = default;
            virtual ~XmlConverter() = default;
        };

        extern XmlConverter CACTO_GRAPHICS_API Converter;

    }

}
