#include <memory>
#include <functional>

#include <SFML/System/Sleep.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>
#include <Cacto/Core/Loader.hpp>

namespace R {
    auto image = cacto::Loader<sf::Image>::fromFile("./res/fondo.png");
    auto texture = cacto::Loader<sf::Texture>::fromFile("./res/fondo.png");
    auto soundBuffer = cacto::Loader<sf::SoundBuffer>::fromFile("./res/track.mp3");
}

int main()
{

    auto image = R::image.get();
    auto texture = R::texture.get();
    auto soundBuffer = R::soundBuffer.get();

    return 0;
}