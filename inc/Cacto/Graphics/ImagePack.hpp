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
        const std::filesystem::path &getPath() const;

        const std::string &getId(const sf::Image &value) const override;
        const sf::Image *const getResource(const std::string &id) const override;

        ImagePack(const std::filesystem::path &path);
        virtual ~ImagePack();

        ImagePack(const ImagePack &other) = delete;
        ImagePack &operator=(const ImagePack &other) = delete;

        ImagePack(ImagePack &&other);
        ImagePack &operator=(ImagePack &&other);

    private:
        std::filesystem::path m_path;
        mutable std::unordered_map<std::string, sf::Image *> m_map;
    };

}
