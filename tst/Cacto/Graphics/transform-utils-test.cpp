#include <sstream>
#include <iostream>
#include <SFML/Graphics/Transform.hpp>
#include <Cacto/Graphics/TransformUtils.hpp>

using cacto::operator<<;
using cacto::operator>>;

int main()
{

    std::stringstream stream{"1,2,3,4,1,5,6,7,1"};
    sf::Transform transform = sf::Transform::Identity;

    stream >> transform;
    std::cout << transform;

    return 0;
}