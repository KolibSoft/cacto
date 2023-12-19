#pragma once

#include <unordered_map>
#include <filesystem>
#include <Cacto/Core/Pack.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace cacto
{

    class TileSet;

    template class CACTO_GRAPHICS_API Pack<TileSet>;

    class CACTO_GRAPHICS_API TileSetPack
        : public virtual Pack<TileSet>
    {

    public:
        const std::string &getId(const Shared<const TileSet> &value) const override;
        Shared<const TileSet> getResource(const std::string &id) const override;
        void setResource(const std::string &id, const Shared<const TileSet> &value) override;

        TileSetPack(const std::filesystem::path &path);
        virtual ~TileSetPack();

    private:
        std::filesystem::path m_path;
        mutable std::unordered_map<std::string, Shared<const TileSet>> m_map;
    };

    const std::string &CACTO_GRAPHICS_API getId(const Shared<const TileSet> &texture);
    Shared<const TileSet> CACTO_GRAPHICS_API getTileSet(const std::string &id);

    extern TileSetPack CACTO_GRAPHICS_API TileSets;

}
