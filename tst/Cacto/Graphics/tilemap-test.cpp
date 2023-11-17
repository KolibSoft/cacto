#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Core/Loader.hpp>
#include <Cacto/Graphics/TileMap.hpp>

namespace R
{
    auto texture = cacto::Loader<sf::Texture>::fromFile("res/fondo.png");
}

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");
    auto texture = R::texture.get();

    cacto::TileMap tileMap{};
    tileMap.setTexture(texture.get());
    tileMap.setTileSize({32, 32});
    tileMap.setArea({{-5, -5}, {10, 10}});
    tileMap.setTiles({{-5, -5}, {10, 10}}, {{0, 0}, {800, 800}});

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
                tileMap.setPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
        }
        window.clear();
        window.draw(tileMap);
        window.display();
    }

    return 0;
}