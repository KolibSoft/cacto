#include <limits>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/Rectangle.hpp>
#include <Cacto/Graphics/Ellipse.hpp>
#include <Cacto/UI/Surface.hpp>
#include <Cacto/UI/Block.hpp>
#include <Cacto/Lang/Utils.hpp>

auto _ = false;

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    cacto::Surface background{};
    background
        .setGeometry(&cacto::Rectangle::Identity)
        .setColor(sf::Color::Red);

    cacto::Block root{};
    root
        .setBackground(&background)
        .setMargin(10)
        .setMinWidth(100)
        .setMaxHeight(100)
        .setPadding(10);

    cacto::toXmlFile(root, "res/block.xml", 4);
    cacto::fromXmlFile(root, "res/block.xml");

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::Resized)
                window.setView(sf::View(sf::FloatRect{{0, 0}, {sf::Vector2f(event.size.width, event.size.height)}}));
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                cacto::fromXmlFile(root, "res/block.xml");
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