#include <iostream>
#include <Cacto/Lang/XmlValue.hpp>

int main()
{

    cacto::XmlValue xml{"Tag", {std::pair{"Attribute", "Value"}, std::pair{"Attribute", "Value"}, std::pair{"Attribute", "Value"}}, {"Text"}};
    xml.asContent().push_back(xml);
    xml.asContent().push_back(xml);
    xml.asContent().push_back(xml);
    xml.asContent().push_back("Text Content");

    std::cout << xml;

    return 0;
}