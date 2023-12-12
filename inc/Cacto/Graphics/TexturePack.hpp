#ifndef CACTO_TEXTURE_PACK_HPP
#define CACTO_TEXTURE_PACK_HPP

#include <unordered_map>
#include <filesystem>
#include <Cacto/Core/Pack.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class Texture;
}

namespace cacto
{

    template class CACTO_GRAPHICS_API Pack<sf::Texture>;

    class CACTO_GRAPHICS_API TexturePack
        : public virtual Pack<sf::Texture>
    {

    public:
        const std::string *const getId(const sf::Texture &value) const override;
        const sf::Texture *const getResource(const std::string &id) const override;
        void setResource(const std::string &id, const sf::Texture *const value) override;

        TexturePack(const std::filesystem::path &path);
        virtual ~TexturePack();

    private:
        std::filesystem::path m_path;
        mutable std::unordered_map<std::string, sf::Texture *> m_map;
    };

    const std::string *const CACTO_GRAPHICS_API getId(const sf::Texture &string);
    const sf::Texture *const CACTO_GRAPHICS_API getTexture(const std::string &id);

    extern TexturePack CACTO_GRAPHICS_API Textures;

}

#endif