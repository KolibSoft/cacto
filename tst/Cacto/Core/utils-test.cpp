#include <iostream>

#include <SFML/System/String.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>

#include <Cacto/Core/StringPack.hpp>

int main()
{

    cacto::StringPack pack{"res/strings"};
    sf::String string = "My String Basic";

    pack.setResource("my_string.txt", &string);
    std::cout << "Content: " << pack.getResource("my_string.txt")->toAnsiString() << "\n";

    string = "My String Content";
    pack.setResource("my_string.txt", &string);
    std::cout << "Content: " << pack.getResource("my_string.txt")->toAnsiString() << "\n";

    auto resource = cacto::Pack<sf::String>::resource("my_string.txt");
    std::cout << "Global Content: " << resource->toAnsiString() << "\n";
    std::cout << "Global Id: " << *cacto::Pack<sf::String>::id(*resource) << "\n";

    return 0;
}