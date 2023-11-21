#include <Cacto/Lang/XmlResource.hpp>

namespace cacto
{

    const Xml *const XmlResource::getXml() const
    {
        return m_xml;
    }

    Xml *const XmlResource::getXml()
    {
        return m_xml;
    }

    XmlValue XmlResource::toXml() const
    {
        if (m_xml)
        {
            auto xml = m_xml->toXml();
            return xml;
        }
        return nullptr;
    }

    void XmlResource::fromXml(const XmlValue &xml)
    {
        drop();
        if (xml != nullptr)
        {
            auto &registry = Registry[xml.getName()];
            if (registry == nullptr)
                throw std::runtime_error("Not registered XML type");
            auto _xml = registry();
            _xml->fromXml(xml);
            m_xml = _xml;
        }
    }

    XmlResource::XmlResource(Xml *const xml)
        : m_xml(xml)
    {
    }

    XmlResource::~XmlResource()
    {
        drop();
    }

    XmlResource::XmlResource(XmlResource &&other)
        : m_xml(nullptr)
    {
        *this = std::move(other);
    }

    XmlResource &XmlResource::operator=(XmlResource &&other)
    {
        drop();
        m_xml = other.m_xml;
        other.m_xml = nullptr;
        return *this;
    }

    std::unordered_map<std::string, std::function<Xml *()>> XmlResource::Registry{};

    void XmlResource::drop()
    {
        if (m_xml)
        {
            delete m_xml;
            m_xml = nullptr;
        }
    }

}