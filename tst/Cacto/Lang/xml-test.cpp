#include <iostream>

#include <Cacto/Lang/XmlValue.hpp>

int main()
{

    cacto::XmlValue xml{};
    auto kind = xml.getType();
    auto comparison = xml == nullptr;

    xml = "Text";
    kind = xml.getType();
    comparison = xml == "Text";
    auto text = xml.asText();

    xml = {"element", {std::pair{"attrA", "valA"}, std::pair{"attrB", "valB"}}, {"Text", {"element", {}}, {"element", {}}, {"element", {}}, {"element", {}}}};
    kind = xml.getType();
    comparison = xml == cacto::XmlValue{"element", {std::pair{"attrA", "valA"}, std::pair{"attrB", "valB"}}, {"Text", {"element", {}}}};
    auto tag = xml.asTag();

    xml[1].append(xml);

    xml = nullptr;
    const auto &cxml = xml;
    std::cout << cxml[0][0][0][0].getAttribute("attribute", "Default");

    return 0;
}