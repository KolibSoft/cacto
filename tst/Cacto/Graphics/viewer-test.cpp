#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/Straight.hpp>
#include <Cacto/Graphics/Bezier.hpp>
#include <Cacto/Graphics/Rectangle.hpp>
#include <Cacto/Graphics/Ellipse.hpp>
#include <Cacto/Graphics/Triangle.hpp>
#include <Cacto/Graphics/LineViewer.hpp>

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    cacto::Straight straight{{10, 10}, {100, 200}};
    cacto::Bezier bezier{{
        {100, 300},
        {200, 100},
        {300, 500},
        {400, 300},
    }};

    cacto::Rectangle rectangle{{100, 10}, {100, 100}};
    cacto::Ellipse ellipse{{200, 200}, {100, 50}};
    cacto::Triangle triangle{{300, 300}, {400, 350}, {350, 400}};

    cacto::LineViewer viewer{};

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        viewer.setLine(&straight);
        viewer.setPrecision(1);
        viewer.setColor(sf::Color::Red);
        viewer.setClosed(false);
        window.draw(viewer);

        viewer.setLine(&bezier);
        viewer.setPrecision(1);
        viewer.setColor(sf::Color::Green);
        viewer.setClosed(false);
        window.draw(viewer);

        viewer.setLine(&rectangle);
        viewer.setPrecision(1);
        viewer.setColor(sf::Color::Blue);
        viewer.setClosed(true);
        window.draw(viewer);

        viewer.setLine(&ellipse);
        viewer.setPrecision(1);
        viewer.setColor(sf::Color::Yellow);
        viewer.setClosed(true);
        window.draw(viewer);

        viewer.setLine(&triangle);
        viewer.setPrecision(1);
        viewer.setColor(sf::Color::Cyan);
        viewer.setClosed(true);
        window.draw(viewer);

        window.display();
    }

    return 0;
}