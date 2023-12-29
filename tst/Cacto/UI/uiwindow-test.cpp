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
#include <Cacto/UI/ScrollLayout.hpp>
#include <Cacto/UI/UIWindow.hpp>
#include <Cacto/Lang/XmlValue.hpp>

auto _ = false;

int main()
{

    cacto::GeometryPack geometries{"."};
    cacto::TexturePack textures{"."};
    cacto::FontPack fonts{"."};

    sf::ContextSettings settings{};
    cacto::UIWindow window{};
    window.create(sf::VideoMode({640, 468}), "SFML Window", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    cacto::Surface bgElement{};
    bgElement
        .setGeometry(cacto::getGeometry("res/rectangle.xml"))
        .setColor(sf::Color::Red);

    cacto::Button element{};
    element
        .setOnClickListener([&](cacto::Node &target, const sf::Event &event)
                            { std::cout << "Clicked\n"; })
        .setBackground(&bgElement)
        .setMargin(10)
        .setFixedWidth(400)
        .setFixedHeight(400)
        .setPadding(10);
    element.asSpan()
        .setFont(cacto::getFont("res/font.ttf"))
        .setString("Text Content")
        .setCharacterSize(32);

    cacto::Surface bgScroll{};
    bgScroll
        .setGeometry(cacto::getGeometry("res/rectangle.xml"))
        .setColor(sf::Color::Green);

    cacto::ScrollLayout scroll{};
    scroll
        .setBackground(&bgScroll)
        .setMargin(10)
        .setFixedWidth(300)
        .setFixedHeight(300)
        .setPadding(10);
    scroll.append(element);

    cacto::Surface bgRoot{};
    bgRoot
        .setGeometry(cacto::getGeometry("res/rectangle.xml"))
        .setColor(sf::Color::Blue);

    cacto::ScrollLayout root{};
    root
        .setBackground(&bgRoot)
        .setMargin(10)
        .setFixedWidth(200)
        .setFixedHeight(200)
        .setPadding(10);
    root.append(scroll);

    window.append(root);

    /*
    cacto::XmlValue xml = nullptr;
    xml.fromFile("res/window.xml");
    cacto::fromXml(window, xml);
    xml = cacto::toXml(window);
    xml.toFile("res/window.xml", 2);
    */

    while (window.isOpen())
    {
        /*
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (root.handle(event))
                break;
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::Resized)
                window.setView(sf::View(sf::FloatRect{{0, 0}, {sf::Vector2f(event.size.width, event.size.height)}}));
        }
        root.compact();
        root.inflate();
        root.place();
        window.clear();
        window.draw(root);
        window.display();
        */
        window.handleContent();
        window.inflateContent();
        window.showContent();
    }

    return 0;
}