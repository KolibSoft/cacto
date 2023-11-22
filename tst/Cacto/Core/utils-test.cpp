#include <iostream>

#include <SFML/System/Sleep.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>

#include <Cacto/Core/Utils.hpp>

int main()
{

    cacto::JsonValue json = nullptr;
    json.fromFile("res/strings.json");

    cacto::StringMap strings{};
    cacto::stringMapFromJson(strings, json);

    strings["mode"] = "DEV";
    std::cout << strings["message"] << '\n';

    json = cacto::stringMapToJson(strings);
    json.toFile("res/strings.json");

    return 0;
}