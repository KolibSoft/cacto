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

int main()
{

    cacto::ColorPack colors{"res/colors.json"};

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
                std::ifstream istream{"res/mesh.xml"};
                istream >> xml;
                mesh.fromXml(xml);
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