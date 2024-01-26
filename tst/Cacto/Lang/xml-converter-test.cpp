#include <iostream>
#include <sstream>
#include <Cacto/Lang/XmlConverter.hpp>

class XmlClass
{

public:
    int value{};

    virtual ~XmlClass() = default;
};

class XmlClassConverter : public virtual cacto::XmlConverter<XmlClass>
{

public:
    cacto::XmlValue toXml(const XmlClass *const value) const override
    {
        if (value && typeid(*value) == typeid(XmlClass))
            return {"XmlClass", {std::pair{"value", std::to_string(value->value)}}};
        return nullptr;
    }

    XmlClass *fromXml(const cacto::XmlValue &xml) const override
    {
        if (xml.isTag() && xml.getName() == "XmlClass")
        {
            auto instance = new XmlClass();
            instance->value = std::stoi(xml["value"]);
            return instance;
        }
        return nullptr;
    }
};

XmlClassConverter Converter{};

class SubXmlClass
    : public XmlClass
{
public:
    int otherValue{};
};

class SubXmlClassConverter
    : public virtual cacto::XmlConverter<SubXmlClass>,
      public virtual XmlClassConverter
{

public:
    cacto::XmlValue toXml(const XmlClass *const value) const override
    {
        if (value)
        {
            auto xml = cacto::toXml(dynamic_cast<const SubXmlClass *>(value));
            return xml;
        }
        return nullptr;
    }

    cacto::XmlValue toXml(const SubXmlClass *const value) const override
    {
        if (value && typeid(*value) == typeid(SubXmlClass))
        {
            auto instance = dynamic_cast<const SubXmlClass *>(value);
            return {"SubXmlClass", {std::pair{"value", std::to_string(value->value)}, std::pair{"otherValue", std::to_string(instance->otherValue)}}};
        }
        return nullptr;
    }

    SubXmlClass *fromXml(const cacto::XmlValue &xml) const override
    {
        if (xml.isTag() && xml.getName() == "SubXmlClass")
        {
            auto instance = new SubXmlClass();
            instance->value = std::stoi(xml["value"]);
            instance->otherValue = std::stoi(xml["otherValue"]);
            return instance;
        }
        return nullptr;
    }
};

SubXmlClassConverter SubConverter{};

class SubSubXmlClass
    : public SubXmlClass
{
public:
    int subOtherValue{};
};

class SubSubXmlClassConverter
    : public virtual cacto::XmlConverter<SubSubXmlClass>,
      public virtual SubXmlClassConverter
{

public:
    cacto::XmlValue toXml(const SubXmlClass *const value) const override
    {
        if (value)
        {
            auto xml = cacto::toXml(dynamic_cast<const SubSubXmlClass *>(value));
            return xml;
        }
        return nullptr;
    }

    cacto::XmlValue toXml(const SubSubXmlClass *const value) const override
    {
        if (value && typeid(*value) == typeid(SubSubXmlClass))
        {
            auto instance = dynamic_cast<const SubSubXmlClass *>(value);
            return {"SubSubXmlClass", {std::pair{"value", std::to_string(value->value)}, std::pair{"otherValue", std::to_string(instance->otherValue)}, std::pair{"subOtherValue", std::to_string(instance->subOtherValue)}}};
        }
        return nullptr;
    }

    SubSubXmlClass *fromXml(const cacto::XmlValue &xml) const override
    {
        if (xml.isTag() && xml.getName() == "SubSubXmlClass")
        {
            auto instance = new SubSubXmlClass();
            instance->value = std::stoi(xml["value"]);
            instance->otherValue = std::stoi(xml["otherValue"]);
            instance->subOtherValue = std::stoi(xml["subOtherValue"]);
            return instance;
        }
        return nullptr;
    }
};

SubSubXmlClassConverter SubSubConverter{};

int main()
{

    std::stringstream text{R"(<SubSubXmlClass value="25" otherValue="200" subOtherValue="300"/>)"};
    cacto::XmlValue xml{};
    text >> xml;
    auto instance = cacto::fromXml<XmlClass>(xml);
    instance->value = 32;
    xml = cacto::toXml(instance);
    std::cout << xml;

    return 0;
}