#include <sstream>
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include <Cacto/Graphics/ColorUtils.hpp>

using cacto::operator<<;
using cacto::operator>>;

int main()
{

    std::stringstream stream{"#aabbccdd"};
    sf::Color color{};

    stream >> color;
    std::cout << color;

    return 0;
}