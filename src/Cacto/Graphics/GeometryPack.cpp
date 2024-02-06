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
            if (pair.second == &value)
                return pair.first;
        return NoId;
    }

    const Geometry *const GeometryPack::getResource(const std::string &id) const
    {
        for (auto &pair : m_map)
            if (pair.first == id)
                return pair.second;
        auto path = m_path / id;
        if (std::filesystem::exists(path))
        {
            Geometry *geometry = nullptr;
            XmlValue xml = nullptr;
            xml.fromFile(path);
            geometry = fromXml<Geometry>(xml);
            m_map.insert({id, geometry});
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

    GeometryPack::~GeometryPack()
    {
        for (auto &pair : m_map)
            if (pair.second)
            {
                delete pair.second;
                pair.second = nullptr;
            }
    }

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

}