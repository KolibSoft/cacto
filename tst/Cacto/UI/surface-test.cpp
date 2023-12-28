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
    cacto::Surface surface{};

    /*
    surface
        .setGeometry(cacto::getGeometry("res/ellipse.xml"))
        .setPrecision(12)
        .setColor(sf::Color::Yellow)
        .setTexture(cacto::getTexture("res/image.png"))
        .setTextureRect({{-100, -100}, {1000, 1000}});
    */
    cacto::fromXmlFile(surface, "res/surface.xml");
    cacto::toXmlFile(surface, "res/surface.xml", 2);

    std::cout << cacto::toXml(surface).toString(2) << '\n';

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::Resized)
                window.setView(sf::View(sf::FloatRect{{0, 0}, {sf::Vector2f(event.size.width, event.size.height)}}));
            else if (event.type == sf::Event::KeyPressed || event.key.code == sf::Keyboard::Space)
                cacto::fromXmlFile(surface, "res/surface.xml");
        }
        surface.compact();
        surface.inflate(sf::Vector2f(window.getSize()));
        surface.place();
        window.clear(sf::Color::Black);
        window.draw(surface);
        window.display();
    }

    return 0;
}