#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/Rectangle.hpp>
#include <Cacto/Graphics/Ellipse.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Collisions/Trace.hpp>

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    sf::Transformable transformable;
    transformable.setOrigin({25, 25});
    transformable.setScale({2, 1});
    transformable.setRotation(sf::degrees(30));
    transformable.setPosition({100, 100});
    auto geometry = std::make_shared<cacto::Rectangle>(sf::Vector2f{0, 0}, sf::Vector2f{50, 50});

    cacto::Trace trace{geometry, transformable.getTransform()};

    std::cout << "Trace size: " << sizeof(cacto::Trace) << "\n";

    auto geometry2 = std::make_shared<cacto::Ellipse>(sf::Vector2f{0, 0}, sf::Vector2f{25, 25});
    auto transformable2 = transformable;

    sf::VertexArray array(sf::PrimitiveType::LineStrip);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        transformable2.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
        cacto::Trace dynamic{geometry2, transformable2.getTransform()};

        if (cacto::zoneWith(trace.getBounds(), dynamic.getBounds()))
        {
            window.clear(sf::Color::Magenta);
            if (trace.checkCollision(dynamic))
                window.clear(sf::Color::White);
        }
        else
            window.clear(sf::Color::Black);

        cacto::setPoints(array, *geometry);
        cacto::setColor(array, sf::Color::Red);
        array.append(array[0]);
        window.draw(array, transformable.getTransform());

        cacto::setPoints(array, *dynamic.getGeometry());
        cacto::setColor(array, sf::Color::Red);
        array.append(array[0]);
        window.draw(array, dynamic.getTransform());

        auto bBounds = trace.getBounds();
        cacto::setPoints(array, cacto::Rectangle({bBounds.left, bBounds.top}, {bBounds.width, bBounds.height}));
        cacto::setColor(array, sf::Color::Blue);
        array.append(array[0]);
        window.draw(array);

        auto dBounds = dynamic.getBounds();
        cacto::setPoints(array, cacto::Rectangle({dBounds.left, dBounds.top}, {dBounds.width, dBounds.height}));
        cacto::setColor(array, sf::Color::Blue);
        array.append(array[0]);
        window.draw(array);

        window.display();
    }

    return 0;
}