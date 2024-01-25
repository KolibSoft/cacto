#include <iostream>
#include <fstream>
#include <Cacto/Lang/XmlValue.hpp>

int main()
{

    cacto::XmlValue xml{};
    std::ifstream fstream{"res/xml.xml"};
    fstream >> xml;
    std::cout << xml;

    return 0;
}