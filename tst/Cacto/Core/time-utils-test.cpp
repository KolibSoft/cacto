#include <sstream>
#include <iostream>
#include <SFML/System/Time.hpp>
#include <Cacto/Core/TimeUtils.hpp>

using cacto::operator<<;
using cacto::operator>>;

int main()
{

    std::stringstream stream{"-200m 20s"};
    sf::Time time{};

    stream >> time;
    std::cout << time;

    return 0;
}