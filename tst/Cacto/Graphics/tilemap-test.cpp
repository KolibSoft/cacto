#include <iostream>

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

    cacto::TileMap tileMap{};
    cacto::XmlValue xml = nullptr;
    xml.fromFile("res/tilemap.xml");
    cacto::fromXml(tileMap, xml);
    xml = cacto::toXml(tileMap);
    xml.toFile("res/tilemap.xml", 2);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                xml.fromFile("res/tilemap.xml");
                cacto::fromXml(tileMap, xml);
            }
        }
        window.clear();
        window.draw(tileMap);
        window.display();
    }

    return 0;
}