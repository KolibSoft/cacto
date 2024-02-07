#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Core/XmlPack.hpp>
#include <Cacto/Core/XmlUtils.hpp>

namespace cacto
{

    std::string getExpression(const XmlValue &xml)
    {
        auto id = getId(xml);
        if (id != "")
        {
            auto expression = "@xml/" + id;
            return std::move(expression);
        }
        return xml.toString();
    }

    XmlValue getXml(const std::string &expression)
    {
        if (expression.compare(0, 5, "@xml/") == 0)
        {
            auto id = expression.substr(5);
            auto resource = getResource<XmlValue>(id);
            if (resource)
                return *resource;
        }
        return expression;
    }

}