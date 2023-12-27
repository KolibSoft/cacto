#pragma once

#include <unordered_map>
#include <filesystem>
#include <Cacto/Core/Pack.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class Font;
}

namespace cacto
{

    template class CACTO_GRAPHICS_API Pack<sf::Font>;

    class CACTO_GRAPHICS_API FontPack
        : public virtual Pack<sf::Font>
    {

    public:
        const std::filesystem::path &getPath() const;

        const std::string &getId(const sf::Font &value) const override;
        const sf::Font *const getResource(const std::string &id) const override;

        FontPack(const std::filesystem::path &path);
        virtual ~FontPack();

    private:
        std::filesystem::path m_path;
        mutable std::unordered_map<std::string, std::shared_ptr<sf::Font>> m_map;
    };

    const std::string &CACTO_GRAPHICS_API getId(const sf::Font &font);
    const sf::Font *const CACTO_GRAPHICS_API getFont(const std::string &id);

}
