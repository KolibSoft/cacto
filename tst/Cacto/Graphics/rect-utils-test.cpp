#include <sstream>
#include <iostream>
#include <SFML/Graphics/Rect.hpp>
#include <Cacto/Graphics/RectUtils.hpp>

using cacto::operator<<;
using cacto::operator>>;

int main()
{

    std::stringstream stream{"10,-10.00,100,100"};
    sf::FloatRect rect{};

    stream >> rect;
    std::cout << rect;

    return 0;
}