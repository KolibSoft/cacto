#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/VertexArrayPack.hpp>
#include <Cacto/Graphics/Mesh.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Lang/Utils.hpp>

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    cacto::Mesh mesh{};
    cacto::fromXmlFile(mesh, "res/mesh.xml");
    std::cout << cacto::toXml(mesh).toString(2) << "\n";
    cacto::toXmlFile(mesh, "res/mesh.xml", 2);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(mesh);
        window.display();
    }

    return 0;
}