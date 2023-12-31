#include <limits>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/Rectangle.hpp>
#include <Cacto/Graphics/Ellipse.hpp>
#include <Cacto/Graphics/GeometryPack.hpp>
#include <Cacto/Graphics/TexturePack.hpp>
#include <Cacto/Graphics/FontPack.hpp>
#include <Cacto/UI/Surface.hpp>
#include <Cacto/UI/Button.hpp>
#include <Cacto/Lang/XmlValue.hpp>

int main()
{

    cacto::GeometryPack geometries{"."};
    cacto::TexturePack textures{"."};
    cacto::FontPack fonts{"."};

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    cacto::Surface background{};
    background
        .setGeometry(cacto::getGeometry("res/rectangle.xml"))
        .setColor(sf::Color::Red);

    cacto::Button root{};
    root
        .setOnClickListener([&](cacto::Node &target, const sf::Event &event)
                            { std::cout << "Clicked\n"; })
        .setHorizontalAnchor(cacto::Box::Center)
        .setVerticalAnchor(cacto::Box::Center)
        .setBackground(&background)
        .setMargin(10)
        .setPadding(10);
    root.asSpan()
        .setFont(cacto::getFont("res/font.ttf"))
        .setString("My Label Text")
        .setCharacterSize(16);

    cacto::XmlValue xml = nullptr;
    xml.fromFile("res/button.xml");
    cacto::fromXml(root, xml);
    xml = cacto::toXml(root);
    xml.toFile("res/button.xml", 2);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (root.handle(event))
            {
                if (event.type == sf::Event::MouseMoved)
                    std::cout << "Set Hand cursor\n";
            }
            else if (event.type == sf::Event::MouseMoved)
                std::cout << "Set Arrow cursor\n";
            else if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::Resized)
                window.setView(sf::View(sf::FloatRect{{0, 0}, {sf::Vector2f(event.size.width, event.size.height)}}));
        }
        root.compact();
        root.inflate(sf::Vector2f{sf::Mouse::getPosition(window)});
        root.place();
        window.clear(sf::Color::Black);
        window.draw(root);
        window.display();
    }

    return 0;
}