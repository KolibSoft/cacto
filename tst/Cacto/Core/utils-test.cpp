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

    pack.setString("my_string.txt", "My String Basis");
    std::cout << "Content:" << pack.getString("my_string.txt").toAnsiString() << "\n";

    pack.setString("my_string.txt", "My String Content");
    std::cout << "Content:" << pack.getString("my_string.txt").toAnsiString() << "\n";

    return 0;
}