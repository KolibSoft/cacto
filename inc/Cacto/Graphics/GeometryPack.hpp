#pragma once

#include <unordered_map>
#include <filesystem>
#include <Cacto/Core/Pack.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace cacto
{

    class Geometry;

    template class CACTO_GRAPHICS_API Pack<Geometry>;

    class CACTO_GRAPHICS_API GeometryPack
        : public virtual Pack<Geometry>
    {

    public:
        const std::string &getId(const Shared<const Geometry> &value) const override;
        Shared<const Geometry> getResource(const std::string &id) const override;
        void setResource(const std::string &id, const Shared<const Geometry> &value) override;

        GeometryPack(const std::filesystem::path &path);
        virtual ~GeometryPack();

    private:
        std::filesystem::path m_path;
        mutable std::unordered_map<std::string, Shared<const Geometry>> m_map;
    };

    const std::string &CACTO_GRAPHICS_API getId(const Shared<const Geometry> &geometry);
    Shared<const Geometry> CACTO_GRAPHICS_API getGeometry(const std::string &id);

}
