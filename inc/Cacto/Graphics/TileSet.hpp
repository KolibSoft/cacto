#pragma once

#include <string>
#include <map>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{

    template <typename T>
    class Rect;

    using FloatRect = Rect<float>;

    class Texture;
}

namespace cacto
{

    class XmlValue;

    class CACTO_GRAPHICS_API TileSet
    {

    public:
        const sf::Texture *const getTexture() const;
        TileSet &setTexture(const sf::Texture *const value);

        const std::string &getId(const sf::FloatRect &tile) const;
        const sf::FloatRect &getTile(const std::string &id) const;

        const std::map<std::string, sf::FloatRect> &asMap() const;
        std::map<std::string, sf::FloatRect> &asMap();

        TileSet();
        virtual ~TileSet();

        static const std::string NoId;
        static const sf::FloatRect NoTile;

    private:
        const sf::Texture *m_texture;
        std::map<std::string, sf::FloatRect> m_map;
    };

    XmlValue CACTO_GRAPHICS_API toXml(const TileSet &tileSet);
    void CACTO_GRAPHICS_API fromXml(TileSet &tileSet, const XmlValue &xml);

}