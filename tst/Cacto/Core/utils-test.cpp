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
    json.fromFile("res/paths.json");

    cacto::PathMap map{};
    cacto::pathMapFromJson(map, json);
    auto path = map["stringId"];

    return 0;
}