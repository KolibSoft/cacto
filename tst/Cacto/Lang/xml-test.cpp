#include <iostream>

#include <Cacto/Lang/XmlValue.hpp>

int main()
{

    cacto::XmlValue xml{};
    auto kind = xml.getKind();
    auto comparison = xml == nullptr;

    xml = "Text";
    kind = xml.getKind();
    comparison = xml == "Text";
    auto text = xml.asText();

    xml = {"element", {std::pair{"attrA", "valA"}, std::pair{"attrB", "valB"}}, {"Text", {"element", {}}, {"element", {}}, {"element", {}}, {"element", {}}}};
    kind = xml.getKind();
    comparison = xml == cacto::XmlValue{"element", {std::pair{"attrA", "valA"}, std::pair{"attrB", "valB"}}, {"Text", {"element", {}}}};
    auto attributes = xml.asAttributes();
    auto content = xml.asContent();

    xml.asContent()[1].asContent().push_back(xml);
    std::cout << xml.toString(2) << '\n';

    xml = "Text: a <element /> tag";
    std::cout << xml.asText() << '\n';
    std::cout << xml.toString() << '\n';
    auto string = xml.toString();
    xml.fromString(string);
    std::cout << xml.toString() << '\n';

    xml.toFile("res/xml.xml", 2);
    xml.fromFile("res/xml.xml");
    std::cout << xml.toString(2) << '\n';

    return 0;
}