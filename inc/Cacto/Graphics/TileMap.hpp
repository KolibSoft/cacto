#pragma once

#include <vector>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Lang/XmlConverter.hpp>
#include <Cacto/Core/ChildNode.hpp>
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
        TileMap &&setOrigin(const sf::Vector2f &value);
        TileMap &&setPosition(const sf::Vector2f &value);
        TileMap &&setScale(const sf::Vector2f &value);
        TileMap &&setRotation(sf::Angle value);

        TileMap &&move(const sf::Vector2f &offset);
        TileMap &&scale(const sf::Vector2f &factors);
        TileMap &&rotate(const sf::Angle &angle);

        const sf::Texture *const getTexture() const;
        TileMap &&setTexture(const sf::Texture *const value);

        const sf::Vector2f &getTileSize() const;
        TileMap &&setTileSize(const sf::Vector2f &value);

        const sf::IntRect &getArea() const;
        TileMap &&setArea(const sf::IntRect &value);

        const sf::FloatRect &getTile(const sf::Vector2i &position) const;
        TileMap &&setTile(const sf::FloatRect &tile, const sf::Vector2i &position);

        TileMap &&setTiles(const sf::FloatRect &tile, const sf::IntRect &area);
        TileMap &&fill(const sf::FloatRect &tile);

        const std::string &getId() const override;
        TileMap &&setId(const std::string &value);

        Node *const getParent() const override;

        void attach(ParentNode &parent) override;
        void detach() override;

        TileMap *clone() const override;
        TileMap *acquire() override;

        TileMap();
        virtual ~TileMap();

        TileMap(const TileMap &other);
        TileMap &operator=(const TileMap &other);

        TileMap(TileMap &&other);
        TileMap &operator=(TileMap &&other);

        static const sf::FloatRect NoTile;

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        const sf::Texture *m_texture;
        sf::Vector2f m_tileSize;
        sf::IntRect m_area;
        std::vector<sf::FloatRect> m_tiles;
        std::string m_id;
        ParentNode *m_parent;

        mutable bool m_invalid;
        mutable sf::VertexArray m_array;
    };

    XmlValue CACTO_GRAPHICS_API toXml(const TileMap &tileMap);
    TileMap CACTO_GRAPHICS_API toTileMap(const XmlValue &xml);

    namespace tile_map
    {

        class CACTO_GRAPHICS_API XmlConverter
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
