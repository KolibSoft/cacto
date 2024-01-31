#include <iostream>
#include <fstream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/Skeleton.hpp>
#include <Cacto/Graphics/ColorPack.hpp>
#include <Cacto/Graphics/TexturePack.hpp>
#include <Cacto/Lang/XmlValue.hpp>

int main()
{

    cacto::ColorPack colors{"res/colors.json"};
    cacto::TexturePack textures{"res/textures"};

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    cacto::Skeleton skeleton{};
    cacto::XmlValue xml = nullptr;

    xml.fromFile("res/skeleton.xml");
    skeleton = cacto::toSkeleton(xml);

    auto left = skeleton.firstDescendant<cacto::Skeleton>("left");
    auto right = skeleton.firstDescendant<cacto::Skeleton>("right");

    auto clone = skeleton;

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
                skeleton.asTransformable().setPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
            else if (event.type == sf::Event::MouseWheelScrolled)
            {
                skeleton.rotate(sf::degrees(event.mouseWheelScroll.delta));
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
        window.draw(clone);
        window.display();
    }

    xml = cacto::toXml(skeleton);
    xml.toFile("res/skeleton.xml");

    return 0;
}