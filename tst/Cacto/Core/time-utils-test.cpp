#include <iostream>
#include <SFML/System/Time.hpp>
#include <Cacto/Core/TimeUtils.hpp>

using cacto::operator<<;

int main()
{

    auto time = sf::seconds(60 * 60 * 30);
    std::cout << time;

    return 0;
}