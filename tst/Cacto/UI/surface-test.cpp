#include <limits>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/Ellipse.hpp>
#include <Cacto/Graphics/TexturePack.hpp>
#include <Cacto/Graphics/GeometryPack.hpp>
#include <Cacto/Lang/Utils.hpp>
#include <Cacto/UI/Surface.hpp>

int main()
{

    cacto::TexturePack textures{"."};
    cacto::GeometryPack geometries{"."};

    std::cout << "Node Converters: " << cacto::XmlConverter<cacto::Node>::getConverterCount() << '\n';

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");
    auto root = std::make_shared<cacto::Surface>();

    (*root)
        .setGeometry(cacto::getGeometry("ellipse.xml"))
        .setPrecision(12)
        .setTexture(cacto::getTexture("fondo.png"))
        .setTextureRect({{-100, -100}, {1000, 1000}});

    cacto::fromXmlFile(*root, "res/surface.xml");
    cacto::toXmlFile(*root, "res/surface.xml", 2);

    std::cout << cacto::toXml(root).toString(2) << '\n';

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
                window.setView(sf::View(sf::FloatRect{{0, 0}, {sf::Vector2f(event.size.width, event.size.height)}}));
        }
        root->compact();
        root->inflate(sf::Vector2f(window.getSize()));
        root->place();
        window.clear(sf::Color::Black);
        window.draw(*root);
        window.display();
    }

    return 0;
}