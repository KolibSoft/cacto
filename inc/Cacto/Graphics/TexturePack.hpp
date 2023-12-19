#pragma once

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
        const std::string &getId(const Shared<const sf::Texture> &value) const override;
        Shared<const sf::Texture> getResource(const std::string &id) const override;
        void setResource(const std::string &id, const Shared<const sf::Texture> &value) override;

        TexturePack(const std::filesystem::path &path);
        virtual ~TexturePack();

    private:
        std::filesystem::path m_path;
        mutable std::unordered_map<std::string, Shared<const sf::Texture>> m_map;
    };

    const std::string &CACTO_GRAPHICS_API getId(const Shared<const sf::Texture> &texture);
    Shared<const sf::Texture> CACTO_GRAPHICS_API getTexture(const std::string &id);

    extern TexturePack CACTO_GRAPHICS_API Textures;

}
