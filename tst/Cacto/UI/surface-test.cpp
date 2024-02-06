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
    cacto::Surface surface{};

    /*
    surface
        .setGeometry(cacto::getGeometry("res/ellipse.xml"))
        .setPrecision(12)
        .setColor(sf::Color::Yellow)
        .setTexture(cacto::getTexture("res/image.png"))
        .setTextureRect({{-100, -100}, {1000, 1000}});
    */
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
                else if (event.key.code == sf::Keyboard::Left)
                    surface.ref<cacto::TransformableChains>().move({-1, 0});
                else if (event.key.code == sf::Keyboard::Right)
                    surface.ref<cacto::TransformableChains>().move({+1, 0});
                else if (event.key.code == sf::Keyboard::Up)
                    surface.ref<cacto::TransformableChains>().move({0, -1});
                else if (event.key.code == sf::Keyboard::Down)
                    surface.ref<cacto::TransformableChains>().move({0, +1});
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