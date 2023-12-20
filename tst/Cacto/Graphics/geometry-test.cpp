#include <iostream>
#include <Cacto/Graphics/GeometryPack.hpp>
#include <Cacto/Graphics/Geometry.hpp>

int main()
{

    cacto::GeometryPack geometries{"res/geometries"};

    auto rectangle = cacto::getGeometry("rectangle.xml");
    std::cout << cacto::toXml(rectangle) << '\n';

    auto ellipse = cacto::getGeometry("ellipse.xml");
    std::cout << cacto::toXml(ellipse) << '\n';

    return 0;
}