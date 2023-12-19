#pragma once

#include <unordered_map>
#include <filesystem>
#include <Cacto/Core/Pack.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class VertexArray;
}

namespace cacto
{

    template class CACTO_GRAPHICS_API Pack<sf::VertexArray>;

    class CACTO_GRAPHICS_API VertexArrayPack
        : public virtual Pack<sf::VertexArray>
    {

    public:
        const std::string &getId(const Shared<const sf::VertexArray> &value) const override;
        Shared<const sf::VertexArray> getResource(const std::string &id) const override;
        void setResource(const std::string &id, const Shared<const sf::VertexArray> &value) override;

        VertexArrayPack(const std::filesystem::path &path);
        virtual ~VertexArrayPack();

    private:
        std::filesystem::path m_path;
        mutable std::unordered_map<std::string, Shared<const sf::VertexArray>> m_map;
    };

    const std::string &CACTO_GRAPHICS_API getId(const Shared<const sf::VertexArray> &image);
    Shared<const sf::VertexArray> CACTO_GRAPHICS_API getVertexArray(const std::string &id);

    extern VertexArrayPack CACTO_GRAPHICS_API VertexArrays;

}
