#include <iostream>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Core/XmlPack.hpp>

int main()
{

    cacto::XmlPack pack{"res/xmls"};
    auto xml = cacto::getResource<cacto::XmlValue>("my_xml.xml");
    std::cout << "Xml content: " << (xml ? *xml : cacto::XmlValue::NoneValue) << '\n';

    return 0;
}