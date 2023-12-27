#include <fstream>
#include <SFML/Graphics/Image.hpp>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Graphics/TileSet.hpp>
#include <Cacto/Graphics/TileSetPack.hpp>

namespace cacto
{

    const std::filesystem::path &TileSetPack::getPath() const
    {
        return m_path;
    }

    const std::string &TileSetPack::getId(const TileSet &value) const
    {
        for (auto &pair : m_map)
            if (pair.second.get() == &value)
                return pair.first;
        return NoId;
    }

    const TileSet *const TileSetPack::getResource(const std::string &id) const
    {
        for (auto &pair : m_map)
            if (pair.first == id)
                return pair.second.get();
        auto path = m_path / id;
        if (std::filesystem::exists(path))
        {
            auto tileSet = std::make_shared<TileSet>();
            XmlValue xml = nullptr;
            xml.fromFile(path);
            cacto::fromXml(*tileSet, xml);
            m_map.insert({id, tileSet});
            return tileSet.get();
        }
        else
        {
            m_map.insert({id, nullptr});
            return nullptr;
        }
    }

    TileSetPack::TileSetPack(const std::filesystem::path &path)
        : m_path(path),
          m_map()
    {
    }

    TileSetPack::~TileSetPack() = default;

    const std::string &getId(const TileSet &tileSet)
    {
        auto &id = Pack<TileSet>::id(tileSet);
        return id;
    }

    const TileSet *const getTileSet(const std::string &id)
    {
        auto tileSet = Pack<TileSet>::resource(id);
        return tileSet;
    }

}