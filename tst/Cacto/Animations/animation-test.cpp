#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/Skeleton.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Animations/Linear.hpp>
#include <Cacto/Animations/Coloring.hpp>
#include <Cacto/Lang/Utils.hpp>

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    cacto::Skeleton skeleton{};
    cacto::fromXmlFile(skeleton, "res/skeleton.xml");
    std::cout << cacto::toXml(skeleton).toString() << "\n";
    cacto::toXmlFile(skeleton, "res/skeleton.xml", 2);

    auto left = skeleton.firstDescendant<cacto::Skeleton>("left");
    auto left_mesh = dynamic_cast<sf::VertexArray *>(left->getChild());
    auto right = skeleton.firstDescendant<cacto::Skeleton>("right");
    auto right_mesh = dynamic_cast<sf::VertexArray *>(right->getChild());

    cacto::Linear linear{1, 2, sf::Time::Zero, sf::seconds(10)};
    cacto::Coloring coloring{sf::Color::Red, sf::Color::Blue, sf::Time::Zero, sf::seconds(10)};
    sf::Time lifetime{};
    bool direction{};

    sf::Clock clock{};
    clock.start();
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

        auto dt = clock.restart();
        if (direction)
        {
            lifetime += dt;
            direction = lifetime < sf::seconds(10);
        }
        else
        {
            lifetime -= dt;
            direction = lifetime < sf::seconds(0);
        }

        auto f = linear.getValue(lifetime);
        auto c = coloring.getValue(lifetime);
        skeleton.setScale({f, f});
        cacto::setColor(*left_mesh, c);
        cacto::setColor(*right_mesh, c);

        window.clear();
        window.draw(skeleton);
        window.display();
    }

    return 0;
}