#include <memory>
#include <functional>

#include <SFML/System/Sleep.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>
#include <Cacto/Core/Loader.hpp>

enum Images
{
    MyImage
};

enum Textures
{
    MyTexture
};

enum Music
{
    MyMusic
};

enum Sound
{
    MySound
};

int main()
{

    cacto::Loader<sf::Image> images;
    images.setLoadFromFile(Images::MyImage, "./res/fondo.png");
    auto image = images.get(Images::MyImage);

    cacto::Loader<sf::Texture> textures;
    textures.setLoadFromImage(Textures::MyTexture, *image);

    cacto::Loader<sf::Music> music;
    music.setOpenFromFile(Music::MyMusic, "./res/track.mp3");

    cacto::Loader<sf::SoundBuffer> sounds;
    sounds.setLoadFromFile(Sound::MySound, "./res/track.mp3");

    {
        auto texture = textures.get(Textures::MyTexture);
        texture = textures.get(Textures::MyTexture);
    }

    {
        auto buffer = sounds.get(Sound::MySound);
        sf::Sound sound{*buffer};
        sound.play();
        sf::sleep(sf::seconds(5));
    }

    {
        auto _music = music.get(Music::MyMusic);
        _music->play();
        sf::sleep(sf::seconds(5));
    }

    return 0;
}