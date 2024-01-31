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
        const std::filesystem::path &getPath() const;

        const std::string &getId(const Geometry &value) const override;
        const Geometry *const getResource(const std::string &id) const override;

        GeometryPack(const std::filesystem::path &path);
        virtual ~GeometryPack();

        GeometryPack(const GeometryPack &other) = delete;
        GeometryPack &operator=(const GeometryPack &other) = delete;

        GeometryPack(GeometryPack &&other);
        GeometryPack &operator=(GeometryPack &&other);

    private:
        std::filesystem::path m_path;
        mutable std::unordered_map<std::string, std::shared_ptr<Geometry>> m_map;
    };

}
