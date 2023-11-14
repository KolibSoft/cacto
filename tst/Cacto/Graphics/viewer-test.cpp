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
        window.draw(viewer);

        viewer.setLine(&bezier);
        viewer.setPrecision(5);
        viewer.setColor(sf::Color::Green);
        window.draw(viewer);

        window.display();
    }

    return 0;
}