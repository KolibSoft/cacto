#pragma once

#include <unordered_map>
#include <filesystem>
#include <SFML/Graphics/Color.hpp>
#include <Cacto/Core/Pack.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace cacto
{

    template class CACTO_GRAPHICS_API Pack<sf::Color>;

    class CACTO_GRAPHICS_API ColorPack
        : public virtual Pack<sf::Color>
    {

    public:
        const std::filesystem::path &getPath() const;

        const std::string &getId(const sf::Color &value) const override;
        const sf::Color *const getResource(const std::string &id) const override;

        ColorPack(const std::filesystem::path &path);
        virtual ~ColorPack();

        ColorPack(const ColorPack &other) = delete;
        ColorPack &operator=(const ColorPack &other) = delete;

        ColorPack(ColorPack &&other);
        ColorPack &operator=(ColorPack &&other);

    private:
        std::filesystem::path m_path;
        mutable std::unordered_map<std::string, std::shared_ptr<sf::Color>> m_map;
    };

    const std::string &CACTO_GRAPHICS_API getId(const sf::Color &color);
    const sf::Color *const CACTO_GRAPHICS_API getColor(const std::string &id);

    std::string CACTO_GRAPHICS_API toAttribute(const sf::Color &color);
    sf::Color CACTO_GRAPHICS_API fromAttribute(const std::string &id, const sf::Color &def = sf::Color::White);

}
