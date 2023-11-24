#ifndef CACTO_TEXTURE_PACK_HPP
#define CACTO_TEXTURE_PACK_HPP

#include <string>
#include <unordered_map>
#include <filesystem>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class Texture;
}

namespace cacto
{

    class CACTO_GRAPHICS_API TexturePack
    {

    public:
        const std::filesystem::path &getPath() const;
        void setPath(const std::filesystem::path &value);

        const sf::Texture &getTexture(const std::string &key, bool refresh = false) const;
        void setTexture(const std::string &key, const sf::Texture &value, bool refresh = false);

        TexturePack(const std::filesystem::path &path = ".");
        virtual ~TexturePack();

    private:
        std::filesystem::path m_path;
        mutable std::unordered_map<std::string, sf::Texture *> m_map;
    };

}

#endif