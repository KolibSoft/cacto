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

    std::ifstream istream{"res/mesh.xml"};
    istream >> xml;
    mesh.fromXml(xml);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    std::ifstream istream{"res/mesh.xml"};
                    istream >> xml;
                    mesh.fromXml(xml);
                }
                else if (event.key.code == sf::Keyboard::Left)
                    mesh.move({-1, 0});
                else if (event.key.code == sf::Keyboard::Right)
                    mesh.move({+1, 0});
                else if (event.key.code == sf::Keyboard::Up)
                    mesh.move({0, -1});
                else if (event.key.code == sf::Keyboard::Down)
                    mesh.move({0, +1});
            }
        }
        window.clear();
        window.draw(mesh);
        window.display();
    }

    std::ofstream ostream{"res/mesh.xml"};
    xml = mesh.toXml();
    ostream << xml;

    return 0;
}