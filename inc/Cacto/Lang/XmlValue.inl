#pragma once

#include <Cacto/Lang/XmlValue.hpp>

namespace cacto
{

    inline bool XmlValue::isEmpty() const
    {
        return getType() == XmlType::Empty;
    }

    inline bool XmlValue::isText() const
    {
        return getType() == XmlType::Text;
    }

    inline XmlValue::operator XmlText() const
    {
        return getText();
    }

    inline bool XmlValue::isTag() const
    {
        return getType() == XmlType::Tag;
    }

    inline XmlValue::operator XmlTag() const
    {
        return getTag();
    }

}