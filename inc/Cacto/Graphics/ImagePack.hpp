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

        const std::string *const getKey(const sf::Image *const value) const;

        const sf::Image &getImage(const std::string &key, bool refresh = false) const;
        void setImage(const std::string &key, const sf::Image &value, bool refresh = false);

        void refreshToFiles() const;
        void refreshFromFiles();

        ImagePack(const std::filesystem::path &path = ".");
        virtual ~ImagePack();

    private:
        std::filesystem::path m_path;
        mutable std::unordered_map<std::string, sf::Image *> m_map;
    };

    const std::string *const CACTO_GRAPHICS_API getKey(const sf::Image *const value);
    const sf::Image &CACTO_GRAPHICS_API getImage(const std::string &key);

    extern std::unordered_map<std::string, ImagePack> CACTO_GRAPHICS_API ImagePacks;

}

#endif