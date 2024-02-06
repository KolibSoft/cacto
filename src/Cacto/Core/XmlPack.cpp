#include <fstream>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Core/XmlPack.hpp>

namespace cacto
{

    const std::filesystem::path &XmlPack::getPath() const
    {
        return m_path;
    }

    const std::string &XmlPack::getId(const XmlValue &value) const
    {
        for (auto &pair : m_map)
            if (*pair.second == value)
                return pair.first;
        return NoId;
    }

    const XmlValue *const XmlPack::getResource(const std::string &id) const
    {
        for (auto &pair : m_map)
            if (pair.first == id)
                return pair.second;
        auto path = m_path / id;
        if (std::filesystem::exists(path))
        {
            auto xml = new XmlValue();
            std::ifstream stream{path};
            stream >> *xml;
            m_map.insert({id, xml});
            return xml;
        }
        else
        {
            m_map.insert({id, nullptr});
            return nullptr;
        }
    }

    XmlPack::XmlPack(const std::filesystem::path &path)
        : m_path(path),
          m_map()
    {
    }

    XmlPack::~XmlPack()
    {
        for (auto &pair : m_map)
            if (pair.second)
            {
                delete pair.second;
                pair.second = nullptr;
            }
    }

    XmlPack::XmlPack(XmlPack &&other)
        : m_path(std::move(other.m_path)),
          m_map(std::move(other.m_map))
    {
    }

    XmlPack &XmlPack::operator=(XmlPack &&other)
    {
        m_path = std::move(other.m_path);
        m_map = std::move(other.m_map);
        return *this;
    }

}