#include <iostream>
#include <fstream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Graphics/Mesh.hpp>
#include <Cacto/Graphics/ColorPack.hpp>
#include <Cacto/Graphics/TexturePack.hpp>

int main()
{

    cacto::ColorPack colors{"res/colors.json"};
    cacto::TexturePack textures{"res/textures"};

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    cacto::Mesh mesh{};
    cacto::XmlValue xml = nullptr;

    xml.fromFile("res/mesh.xml");
    mesh = cacto::toMesh(xml);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                mesh.locate(sf::Vector2f(sf::Mouse::getPosition(window)));
            }
            else if (event.type == sf::Event::MouseWheelScrolled)
            {
                mesh.rotate(sf::degrees(event.mouseWheelScroll.delta));
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    xml.fromFile("res/mesh.xml");
                    mesh = cacto::toMesh(xml);
                }
                else if (event.key.code == sf::Keyboard::Left)
                    mesh.acquire({-1, 0});
                else if (event.key.code == sf::Keyboard::Right)
                    mesh.acquire({+1, 0});
                else if (event.key.code == sf::Keyboard::Up)
                    mesh.acquire({0, -1});
                else if (event.key.code == sf::Keyboard::Down)
                    mesh.acquire({0, +1});
            }
        }
        window.clear();
        window.draw(mesh);
        window.display();
    }

    xml = cacto::toXml(mesh);
    xml.toFile("res/mesh.xml");

    return 0;
}