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

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");
    cacto::XmlValue xml = nullptr;
    auto surface = cacto::Surface()
                       .setGeometry(cacto::getResource<cacto::Geometry>("res/ellipse.xml"))
                       .setPrecision(12)
                       .setColor(sf::Color::Yellow)
                       .setTexture(cacto::getResource<sf::Texture>("res/image.png"))
                       .setTextureRect({{-100, -100}, {1000, 1000}});

    xml.fromFile("res/surface.xml");
    surface = cacto::toSurface(xml);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::Resized)
                window.setView(sf::View(sf::FloatRect{{0, 0}, {sf::Vector2f(event.size.width, event.size.height)}}));
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    xml.fromFile("res/surface.xml");
                    surface = cacto::toSurface(xml);
                }
            }
        }

        surface.compact();
        surface.inflate(sf::Vector2f(window.getSize()));
        surface.place();

        if (surface.containsVisualPoint(sf::Vector2f(sf::Mouse::getPosition(window))))
            window.clear(sf::Color::Green);
        else
            window.clear(sf::Color::Black);

        window.draw(surface);
        window.display();
    }

    xml = cacto::toXml(surface);
    xml.toFile("res/surface.xml");

    return 0;
}