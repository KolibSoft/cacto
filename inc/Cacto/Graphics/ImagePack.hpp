#ifndef CACTO_IMAGE_PACK_HPP
#define CACTO_IMAGE_PACK_HPP

#include <string>
#include <unordered_map>
#include <filesystem>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class Image;
}

namespace cacto
{

    class CACTO_GRAPHICS_API ImagePack
    {

    public:
        const std::filesystem::path &getPath() const;
        void setPath(const std::filesystem::path &value);

        const sf::Image &getImage(const std::string &key, bool refresh = false) const;
        void setImage(const std::string &key, const sf::Image &value, bool refresh = false);

        ImagePack(const std::filesystem::path &path = ".");
        virtual ~ImagePack();

    private:
        std::filesystem::path m_path;
        mutable std::unordered_map<std::string, sf::Image *> m_map;
    };

}

#endif