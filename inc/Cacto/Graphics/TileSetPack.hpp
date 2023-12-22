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
        const std::string &getId(const TileSet &value) const override;
        const TileSet *const getResource(const std::string &id) const override;

        TileSetPack(const std::filesystem::path &path);
        virtual ~TileSetPack();

    private:
        std::filesystem::path m_path;
        mutable std::unordered_map<std::string, std::shared_ptr<TileSet>> m_map;
    };

    const std::string &CACTO_GRAPHICS_API getId(const TileSet &tileSet);
    const TileSet *const CACTO_GRAPHICS_API getTileSet(const std::string &id);

}
