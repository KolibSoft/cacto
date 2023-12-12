#ifndef CACTO_IMAGE_PACK_HPP
#define CACTO_IMAGE_PACK_HPP

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
        const std::string *const getId(const sf::Image &value) const override;
        const sf::Image *const getResource(const std::string &id) const override;
        void setResource(const std::string &id, const sf::Image *const value) override;

        ImagePack(const std::filesystem::path &path);
        virtual ~ImagePack();

    private:
        std::filesystem::path m_path;
        mutable std::unordered_map<std::string, sf::Image *> m_map;
    };

    const std::string *const CACTO_GRAPHICS_API getId(const sf::Image &string);
    const sf::Image *const CACTO_GRAPHICS_API getImage(const std::string &id);

    extern ImagePack CACTO_GRAPHICS_API Images;

}

#endif