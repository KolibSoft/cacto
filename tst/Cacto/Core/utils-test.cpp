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

    cacto::StringPack pack{"res/strings.json"};
    auto string = cacto::getString("my_string");
    std::cout << "String content: " << (string ? string->toAnsiString() : "No Content") << '\n';

    return 0;
}