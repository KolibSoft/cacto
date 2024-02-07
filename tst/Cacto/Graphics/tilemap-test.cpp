#include <iostream>
#include <fstream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/TileMap.hpp>
#include <Cacto/Graphics/RectPack.hpp>
#include <Cacto/Graphics/TexturePack.hpp>
#include <Cacto/Graphics/ImagePack.hpp>
#include <Cacto/Lang/XmlValue.hpp>

int main()
{

    cacto::TexturePack textures{"."};
    cacto::RectPack rects{"res/rects.json"};

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    auto tileMap = cacto::TileMap()
                       .setTexture(cacto::getResource<sf::Texture>("res/tiles.png"))
                       .setArea({{0, 0}, {10, 10}})
                       .setTileSize({32, 32})
                       .setTiles(*cacto::getResource<sf::FloatRect>("Pilar"), {{0, 0}, {10, 10}});
    cacto::XmlValue xml = nullptr;

    xml.fromFile("res/tilemap.xml");
    tileMap = cacto::toTileMap(xml);
    auto clone = tileMap;

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                tileMap.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                xml.fromFile("res/tilemap.xml");
                tileMap = cacto::toTileMap(xml);
            }
        }
        window.clear(sf::Color::White);
        window.draw(tileMap);
        window.draw(clone);
        window.display();
    }

    xml = cacto::toXml(tileMap);
    xml.toFile("res/tilemap.xml");

    return 0;
}