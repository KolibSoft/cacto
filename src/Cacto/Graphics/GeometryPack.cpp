#include <fstream>
#include <SFML/Graphics/Image.hpp>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Graphics/Geometry.hpp>
#include <Cacto/Graphics/GeometryPack.hpp>

namespace cacto
{

    const std::string &GeometryPack::getId(const Shared<const Geometry> &value) const
    {
        for (auto &pair : m_map)
            if (pair.second == value)
                return pair.first;
        return NoId;
    }

    Shared<const Geometry> GeometryPack::getResource(const std::string &id) const
    {
        for (auto &pair : m_map)
            if (pair.first == id)
                return pair.second;
        auto path = m_path / id;
        if (std::filesystem::exists(path))
        {
            auto geometry = std::make_shared<Geometry>();
            XmlValue xml = nullptr;
            xml.fromFile(path);
            cacto::fromXml(*geometry, xml);
            m_map.insert({id, geometry});
            return geometry;
        }
        else
        {
            m_map.insert({id, nullptr});
            return nullptr;
        }
    }

    void GeometryPack::setResource(const std::string &id, const Shared<const Geometry> &value)
    {
        for (auto &pair : m_map)
            if (pair.first == id)
            {
                pair.second = value;
                return;
            }
        if (value)
        {
            auto path = m_path / id;
            XmlValue xml = nullptr;
            xml = cacto::toXml(*value);
            xml.toFile(path);
            m_map.insert({id, value});
        }
        else
        {
            if (std::filesystem::remove(m_path / id))
                m_map.insert({id, nullptr});
        }
    }

    GeometryPack::GeometryPack(const std::filesystem::path &path)
        : m_path(path),
          m_map()
    {
    }

    GeometryPack::~GeometryPack() = default;

    const std::string &getId(const Shared<const Geometry> &geometry)
    {
        auto &id = Pack<Geometry>::id(geometry);
        return id;
    }

    Shared<const Geometry> getGeometry(const std::string &id)
    {
        auto geometry = Pack<Geometry>::resource(id);
        return std::move(geometry);
    }

}