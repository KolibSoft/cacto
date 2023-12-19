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
        const std::string &getId(const Shared<const sf::Image> &value) const override;
        Shared<const sf::Image> getResource(const std::string &id) const override;
        void setResource(const std::string &id, const Shared<const sf::Image> &value) override;

        ImagePack(const std::filesystem::path &path);
        virtual ~ImagePack();

    private:
        std::filesystem::path m_path;
        mutable std::unordered_map<std::string, Shared<const sf::Image>> m_map;
    };

    const std::string &CACTO_GRAPHICS_API getId(const Shared<const sf::Image> &image);
    Shared<const sf::Image> CACTO_GRAPHICS_API getImage(const std::string &id);

    extern ImagePack CACTO_GRAPHICS_API Images;

}
