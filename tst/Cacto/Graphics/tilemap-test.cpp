#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/TileMap.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Graphics/TexturePack.hpp>
#include <Cacto/Graphics/TileSet.hpp>
#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Lang/Utils.hpp>
#include <Cacto/Core/Utils.hpp>

int main()
{

    cacto::TexturePack pack{"res/textures"};
    cacto::TileSet tileSet{};

    cacto::fromXmlFile(tileSet, "res/tile_set.xml");
    cacto::toXmlFile(tileSet, "res/tile_set.xml", 2);

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    cacto::TileMap tileMap{};
    cacto::fromXmlFile(tileMap, "res/tile_map.xml");
    // cacto::toXmlFile(tileMap, "res/tile_map.xml", 2);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                cacto::fromXmlFile(tileMap, "res/tile_map.xml");
        }
        window.clear();
        window.draw(tileMap);
        window.display();
    }

    return 0;
}