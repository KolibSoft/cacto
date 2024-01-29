#include <sstream>
#include <iostream>
#include <SFML/System/Angle.hpp>
#include <Cacto/Core/AngleUtils.hpp>

using cacto::operator<<;
using cacto::operator>>;

int main()
{

    std::stringstream stream{"-100deg"};
    sf::Angle angle{};

    stream >> angle;
    std::cout << angle;

    return 0;
}