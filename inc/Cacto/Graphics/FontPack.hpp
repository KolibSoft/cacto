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
        const std::string &getId(const Shared<const sf::Font> &value) const override;
        Shared<const sf::Font> getResource(const std::string &id) const override;
        void setResource(const std::string &id, const Shared<const sf::Font> &value) override;

        FontPack(const std::filesystem::path &path);
        virtual ~FontPack();

    private:
        std::filesystem::path m_path;
        mutable std::unordered_map<std::string, Shared<const sf::Font>> m_map;
    };

    const std::string &CACTO_GRAPHICS_API getId(const Shared<const sf::Font> &font);
    Shared<const sf::Font> CACTO_GRAPHICS_API getFont(const std::string &id);

}
