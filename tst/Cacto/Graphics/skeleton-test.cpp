#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/Skeleton.hpp>
#include <Cacto/Graphics/ColorPack.hpp>
#include <Cacto/Lang/XmlValue.hpp>

int main()
{

    cacto::ColorPack colors{"res/colors.json"};

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    cacto::Skeleton skeleton{};

    auto stackSize = cacto::Node::XmlStack.getSize();
    cacto::XmlValue xml = nullptr;
    xml.fromFile("res/skeleton.xml");
    cacto::fromXml(skeleton, xml);
    xml = cacto::toXml(skeleton);
    xml.toFile("res/skeleton.xml", 2);

    std::cout << "Node Xml Stack: " << cacto::Node::XmlStack.getSize() << '\n';
    auto stack = cacto::Node::XmlStack.pop(cacto::Node::XmlStack.getSize() - stackSize);
    std::cout << "Node Xml Stack: " << cacto::Node::XmlStack.getSize() << '\n';
    std::cout << "Taken Stack: " << stack.size() << '\n';

    auto left = skeleton.firstDescendant<cacto::Skeleton>("left");
    auto right = skeleton.firstDescendant<cacto::Skeleton>("right");

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
                skeleton.setPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
            else if (event.type == sf::Event::MouseWheelScrolled)
            {
                skeleton.rotate(sf::degrees(event.mouseWheelScroll.delta));
                skeleton.setScale(skeleton.getScale() + sf::Vector2f{event.mouseWheelScroll.delta / 100, -event.mouseWheelScroll.delta / 100});
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                    left->rotate(sf::degrees(5));
                else if (event.key.code == sf::Keyboard::Right)
                    right->rotate(sf::degrees(5));
            }
        }
        window.clear();
        window.draw(skeleton);
        window.display();
    }

    return 0;
}