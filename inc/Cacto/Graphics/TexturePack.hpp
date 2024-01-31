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
        const std::filesystem::path &getPath() const;

        const std::string &getId(const sf::Texture &value) const override;
        const sf::Texture *const getResource(const std::string &id) const override;

        TexturePack(const std::filesystem::path &path);
        virtual ~TexturePack();

        TexturePack(const TexturePack &other) = delete;
        TexturePack &operator=(const TexturePack &other) = delete;

        TexturePack(TexturePack &&other);
        TexturePack &operator=(TexturePack &&other);

    private:
        std::filesystem::path m_path;
        mutable std::unordered_map<std::string, std::shared_ptr<sf::Texture>> m_map;
    };

}
