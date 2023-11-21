#ifndef CACTO_XML_RESOURCE_HPP
#define CACTO_XML_RESOURCE_HPP

#include <functional>
#include <Cacto/Lang/Xml.hpp>

namespace cacto
{

    class CACTO_LANG_API XmlResource
        : public virtual Xml
    {

    public:
        const Xml *const getXml() const;
        Xml *const getXml();

        XmlValue toXml() const override;
        void fromXml(const XmlValue &xml) override;

        XmlResource(Xml *const xml = nullptr);
        virtual ~XmlResource();

        XmlResource(const XmlResource &other) = delete;
        XmlResource &operator=(const XmlResource &other) = delete;

        XmlResource(XmlResource &&other);
        XmlResource &operator=(XmlResource &&other);

        static std::unordered_map<std::string, std::function<Xml *()>> Registry;

    private:
        void drop();

        Xml *m_xml;
    };

}

#endif