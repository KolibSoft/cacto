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
#include <Cacto/UI/Surface.hpp>
#include <Cacto/UI/VirtualLayout.hpp>
#include <Cacto/Lang/XmlValue.hpp>

auto _ = false;

class Element : public cacto::Block
{

public:
    bool handle(const sf::Event &event) override
    {
        if (event.type == sf::Event::MouseMoved && containsVisualPoint({float(event.mouseMove.x), float(event.mouseMove.y)}))
        {
            std::cout << "Hovered\n";
        }
        return Block::handle(event);
    }
};

int main()
{

    cacto::GeometryPack geometries{"."};
    cacto::TexturePack textures{"."};

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    cacto::Surface bgBlock{};
    bgBlock
        .setGeometry(cacto::getGeometry("res/rectangle.xml"))
        .setColor(sf::Color::Red);

    Element element{};
    element
        .setBackground(&bgBlock)
        .setMargin(10)
        .setFixedWidth(100)
        .setFixedHeight(100)
        .setPadding(10);

    cacto::Surface bgRoot{};
    bgRoot
        .setGeometry(cacto::getGeometry("res/rectangle.xml"))
        .setColor(sf::Color::Blue);

    cacto::VirtualLayout root{};
    root
        .setHorizontalAnchor(cacto::Box::Center)
        .setVerticalAnchor(cacto::Box::Center)
        .setBackground(&bgRoot)
        .setMargin(10)
        .setFixedWidth(200)
        .setFixedHeight(200)
        .setPadding(10);
    root.append(element);

    /*
    cacto::XmlValue xml = nullptr;
    xml.fromFile("res/virtual.xml");
    cacto::fromXml(root, xml);
    xml = cacto::toXml(root);
    xml.toFile("res/virtual.xml", 2);
    */

    sf::Transformable transformable{};
    transformable.move({100, 100});
    transformable.rotate(sf::degrees(15));

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (root.handle(event))
                break;
            else if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::Resized)
                window.setView(sf::View(sf::FloatRect{{0, 0}, {sf::Vector2f(event.size.width, event.size.height)}}));
            else if (event.type == sf::Event::MouseWheelScrolled)
            {
                root.asTransformable().move({event.mouseWheelScroll.delta, 0});
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                /*
                xml.fromFile("res/virtual.xml");
                cacto::fromXml(root, xml);
                */
            }
        }
        root.compact();
        root.inflate();
        root.place();
        window.clear();
        window.draw(root, transformable.getTransform());
        window.display();
    }

    return 0;
}