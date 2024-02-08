#pragma once

#include <unordered_map>
#include <filesystem>
#include <Cacto/Core/Pack.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{

    template <typename T>
    class Rect;

    using FloatRect = Rect<float>;

}

namespace cacto
{

    template class CACTO_GRAPHICS_API Pack<sf::FloatRect>;

    class CACTO_GRAPHICS_API RectPack
        : public virtual Pack<sf::FloatRect>
    {

    public:
        const std::filesystem::path &getPath() const;

        const std::string &getId(const sf::FloatRect &value) const override;
        const sf::FloatRect *const getResource(const std::string &id) const override;

        RectPack(const std::filesystem::path &path);
        virtual ~RectPack();

        RectPack(const RectPack &other) = delete;
        RectPack &operator=(const RectPack &other) = delete;

        RectPack(RectPack &&other);
        RectPack &operator=(RectPack &&other);

    private:
        void load() const;

        std::filesystem::path m_path;
        mutable bool m_loaded;
        mutable std::unordered_map<std::string, sf::FloatRect *> m_map;
    };

}
