#pragma once

#include <unordered_map>
#include <filesystem>
#include <Cacto/Core/Pack.hpp>
#include <Cacto/Core/Export.hpp>

namespace cacto
{

    class XmlValue;

    template class CACTO_CORE_API Pack<XmlValue>;

    class CACTO_CORE_API XmlPack
        : public virtual Pack<XmlValue>
    {

    public:
        const std::filesystem::path &getPath() const;

        const std::string &getId(const XmlValue &value) const override;
        const XmlValue *const getResource(const std::string &id) const override;

        XmlPack(const std::filesystem::path &path);
        virtual ~XmlPack();

        XmlPack(const XmlPack &other) = delete;
        XmlPack &operator=(const XmlPack &other) = delete;

        XmlPack(XmlPack &&other);
        XmlPack &operator=(XmlPack &&other);

    private:
        std::filesystem::path m_path;
        mutable std::unordered_map<std::string, std::shared_ptr<XmlValue>> m_map;
    };

    const std::string &CACTO_CORE_API getId(const XmlValue &xml);
    const XmlValue *const CACTO_CORE_API getXml(const std::string &id);

}
