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
#include <Cacto/Lang/XmlValue.hpp>
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
    cacto::XmlValue xml = nullptr;
    xml.fromFile("res/surface.xml");
    cacto::fromXml(surface, xml);
    xml = cacto::toXml(surface);
    xml.toFile("res/surface.xml", 2);

    std::cout << cacto::toXml(surface).toString(2) << '\n';

    sf::Transformable transformable{};
    transformable.scale({0.5, 0.5});
    transformable.move({200, 200});
    transformable.rotate(sf::degrees(30));

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
            {
                xml.fromFile("res/surface.xml");
                cacto::fromXml(surface, xml);
            }
        }

        surface.compact();
        surface.inflate(sf::Vector2f(window.getSize()));
        surface.place();

        if (surface.containsVisually(sf::Vector2f(sf::Mouse::getPosition(window))))
            window.clear(sf::Color::Green);
        else
            window.clear(sf::Color::Black);

        window.draw(surface, transformable.getTransform());
        window.display();
    }

    return 0;
}