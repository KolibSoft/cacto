#include <iostream>
#include <Cacto/Lang/XmlValue.hpp>

int main()
{

    cacto::XmlValue xml{"Tag", {std::pair{"A", "B"}}, {"Text", {"Tag", {}}, "Text", {"Tag", {}}, "Text", {"Tag", {}}}};
    std::cout << xml;

    return 0;
}