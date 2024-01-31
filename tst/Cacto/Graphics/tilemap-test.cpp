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

    cacto::TileMap tileMap{};
    cacto::XmlValue xml = nullptr;

    std::ifstream istream{"res/tilemap.xml"};
    istream >> xml;
    tileMap.fromXml(xml);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                std::ifstream istream{"res/tilemap.xml"};
                istream >> xml;
                tileMap.fromXml(xml);
            }
        }
        window.clear();
        window.draw(tileMap);
        window.display();
    }

    std::ofstream ostream{"res/tilemap.xml"};
    xml = tileMap.toXml();
    ostream << xml;

    return 0;
}