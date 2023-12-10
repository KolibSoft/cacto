#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Graphics/Mesh.hpp>

int main()
{

    std::cout << "Node Converters: " << cacto::XmlConverter<cacto::Node>::Converters.size() << "\n";

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    cacto::Mesh mesh{};
    cacto::fromXmlFile(mesh, "res/mesh.xml");
    cacto::toXmlFile(mesh, "res/mesh.xml", 2);

    cacto::Node *node = nullptr;
    cacto::fromXmlFile(node, "res/mesh.xml");
    auto value = cacto::toXml(&mesh).toString();

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw((sf::VertexArray &)mesh);
        window.display();
    }

    std::cout << "Node Converters: " << cacto::XmlConverter<cacto::Node>::Converters.size() << "\n";

    return 0;
}