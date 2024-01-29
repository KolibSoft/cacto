#include <iostream>
#include <SFML/System/String.hpp>
#include <Cacto/Core/StringPack.hpp>

int main()
{

    cacto::StringPack pack{"res/strings.json"};
    auto string = cacto::getResource<sf::String>("my_string");
    std::cout << "String content: " << (string ? string->toAnsiString() : "No Content") << '\n';

    return 0;
}