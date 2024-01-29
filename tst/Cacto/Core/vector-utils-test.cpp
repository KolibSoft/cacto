#include <sstream>
#include <iostream>
#include <SFML/System/Vector2.hpp>
#include <Cacto/Core/VectorUtils.hpp>

using cacto::operator<<;
using cacto::operator>>;

int main()
{

    std::stringstream stream{"-100.34,+100.45"};
    sf::Vector2f vector{};

    stream >> vector;
    std::cout << vector;

    return 0;
}