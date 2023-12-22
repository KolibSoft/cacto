#pragma once

#include <unordered_map>
#include <filesystem>
#include <Cacto/Core/Pack.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class Image;
}

namespace cacto
{

    template class CACTO_GRAPHICS_API Pack<sf::Image>;

    class CACTO_GRAPHICS_API ImagePack
        : public virtual Pack<sf::Image>
    {

    public:
        const std::string &getId(const sf::Image &value) const override;
        const sf::Image *const getResource(const std::string &id) const override;

        ImagePack(const std::filesystem::path &path);
        virtual ~ImagePack();

    private:
        std::filesystem::path m_path;
        mutable std::unordered_map<std::string, std::shared_ptr<sf::Image>> m_map;
    };

    const std::string &CACTO_GRAPHICS_API getId(const sf::Image &image);
    const sf::Image *const CACTO_GRAPHICS_API getImage(const std::string &id);

}
