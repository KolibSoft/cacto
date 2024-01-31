#include <fstream>
#include <SFML/Graphics/Image.hpp>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Graphics/Geometry.hpp>
#include <Cacto/Graphics/GeometryPack.hpp>

namespace cacto
{

    const std::filesystem::path &GeometryPack::getPath() const
    {
        return m_path;
    }

    const std::string &GeometryPack::getId(const Geometry &value) const
    {
        for (auto &pair : m_map)
            if (pair.second.get() == &value)
                return pair.first;
        return NoId;
    }

    const Geometry *const GeometryPack::getResource(const std::string &id) const
    {
        for (auto &pair : m_map)
            if (pair.first == id)
                return pair.second.get();
        auto path = m_path / id;
        if (std::filesystem::exists(path))
        {
            Geometry *geometry = nullptr;
            XmlValue xml = nullptr;
            xml.fromFile(path);
            geometry = fromXml<Geometry>(xml);
            m_map.insert({id, std::shared_ptr<Geometry>(geometry)});
            return geometry;
        }
        else
        {
            m_map.insert({id, nullptr});
            return nullptr;
        }
    }

    GeometryPack::GeometryPack(const std::filesystem::path &path)
        : m_path(path),
          m_map()
    {
    }

    GeometryPack::~GeometryPack() = default;

    GeometryPack::GeometryPack(GeometryPack &&other)
        : m_path(std::move(other.m_path)),
          m_map(std::move(other.m_map))
    {
    }

    GeometryPack &GeometryPack::operator=(GeometryPack &&other)
    {
        m_path = std::move(other.m_path);
        m_map = std::move(other.m_map);
        return *this;
    }

    const std::string &getId(const Geometry &geometry)
    {
        auto &id = Pack<Geometry>::id(geometry);
        return id;
    }

    const Geometry *const getGeometry(const std::string &id)
    {
        auto geometry = Pack<Geometry>::resource(id);
        return geometry;
    }

}