#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/Rectangle.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Collisions/Body.hpp>

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    auto geometry = std::make_shared<cacto::Rectangle>(sf::Vector2f{10, 10}, sf::Vector2f{50, 50});
    cacto::Body body;
    body.setGeometry(geometry);
    body.setOrigin({25, 25});
    body.setScale({2, 1});
    body.setRotation(sf::degrees(30));
    body.setPosition({100, 100});

    sf::VertexArray array(sf::PrimitiveType::TriangleFan);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (geometry->containsPoint(body.getInverseTransform().transformPoint(sf::Vector2f(sf::Mouse::getPosition(window)))))
            window.clear(sf::Color::White);
        else
            window.clear(sf::Color::Black);
        cacto::setPoints(array, *geometry);
        cacto::setColor(array, sf::Color::Red);
        window.draw(array, body.getTransform());
        window.display();
    }

    return 0;
}