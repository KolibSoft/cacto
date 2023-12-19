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
        const Shared<const sf::Texture> &getTexture() const;
        TileSet &setTexture(const Shared<const sf::Texture> &value);

        const std::map<std::string, sf::FloatRect> &asMap() const;
        std::map<std::string, sf::FloatRect> &asMap();
        const sf::FloatRect &operator[](const std::string &id) const;
        sf::FloatRect &operator[](const std::string &id);

        TileSet();
        virtual ~TileSet();

    private:
        Shared<const sf::Texture> m_texture;
        mutable std::map<std::string, sf::FloatRect> m_map;
    };

    XmlValue CACTO_GRAPHICS_API toXml(const TileSet &tileSet);
    void CACTO_GRAPHICS_API fromXml(TileSet &tileSet, const XmlValue &xml);

}