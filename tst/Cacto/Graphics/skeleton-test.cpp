#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/Skeleton.hpp>
#include <Cacto/UI/Surface.hpp>

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    cacto::Skeleton skeleton{};

    auto body = cacto::Surface::Rectangle;
    body.inflate({100, 100});
    body.setColor(sf::Color::Red);

    auto bone = cacto::Surface::Rectangle;
    bone.inflate({75, 75});
    bone.setColor(sf::Color::Blue);

    skeleton
        .append(body)
        .setCoord({0, 0})
        .setRelation(cacto::Skeleton::Body);
    skeleton
        .append(bone)
        .setCoord({50, 50})
        .setRelation(cacto::Skeleton::Bone);

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
        }
        window.clear();
        window.draw(skeleton);
        window.display();
    }

    return 0;
}