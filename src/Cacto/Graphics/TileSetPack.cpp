#include <fstream>
#include <SFML/Graphics/Image.hpp>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Graphics/TileSet.hpp>
#include <Cacto/Graphics/TileSetPack.hpp>

namespace cacto
{

    const std::string &TileSetPack::getId(const Shared<const TileSet> &value) const
    {
        for (auto &pair : m_map)
            if (pair.second == value)
                return pair.first;
        return NoId;
    }

    Shared<const TileSet> TileSetPack::getResource(const std::string &id) const
    {
        for (auto &pair : m_map)
            if (pair.first == id)
                return pair.second;
        auto path = m_path / id;
        if (std::filesystem::exists(path))
        {
            auto tileSet = std::make_shared<TileSet>();
            XmlValue xml = nullptr;
            xml.fromFile(path);
            cacto::fromXml(*tileSet, xml);
            m_map.insert({id, tileSet});
            return tileSet;
        }
        else
        {
            m_map.insert({id, nullptr});
            return nullptr;
        }
    }

    void TileSetPack::setResource(const std::string &id, const Shared<const TileSet> &value)
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

    TileSetPack::TileSetPack(const std::filesystem::path &path)
        : m_path(path),
          m_map()
    {
    }

    TileSetPack::~TileSetPack() = default;

    const std::string &getId(const Shared<const TileSet> &tileSet)
    {
        auto &id = Pack<TileSet>::id(tileSet);
        return id;
    }

    Shared<const TileSet> getTileSet(const std::string &id)
    {
        auto tileSet = Pack<TileSet>::resource(id);
        return std::move(tileSet);
    }

}