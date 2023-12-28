#include <limits>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/Rectangle.hpp>
#include <Cacto/Graphics/Ellipse.hpp>
#include <Cacto/Graphics/GeometryPack.hpp>
#include <Cacto/Graphics/TexturePack.hpp>
#include <Cacto/UI/Surface.hpp>
#include <Cacto/UI/FrameLayout.hpp>
#include <Cacto/Lang/Utils.hpp>

auto _ = false;

int main()
{

    cacto::GeometryPack geometries{"."};
    cacto::TexturePack textures{"."};

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    cacto::Surface bgBlock{};
    bgBlock
        .setGeometry(cacto::getGeometry("res/rectangle.xml"))
        .setColor(sf::Color::Red);

    cacto::Block block{};
    block
        .setBackground(&bgBlock)
        .setMargin(10)
        .setMinWidth(100)
        .setMaxHeight(100)
        .setPadding(10);

    cacto::Surface bgRoot{};
    bgRoot
        .setGeometry(cacto::getGeometry("res/rectangle.xml"))
        .setColor(sf::Color::Blue);

    cacto::FrameLayout root{};
    root
        .setBackground(&bgRoot)
        .setMargin(10)
        .setMinWidth(100)
        .setMaxHeight(100)
        .setPadding(10);
    root.append(block);

    // cacto::toXmlFile(root, "res/frame.xml", 4);
    // cacto::fromXmlFile(root, "res/frame.xml");

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
                ; // cacto::fromXmlFile(root, "res/frame.xml");
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