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
#include <Cacto/Graphics/VertexArrayUtils.hpp>

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");
    cacto::XmlValue xml = nullptr;

    cacto::Straight straight{{10, 10}, {100, 200}};
    xml = toXml(straight);
    xml.toFile("res/straight.xml");
    xml.fromFile("res/straight.xml");
    straight = cacto::toStraight(xml);

    cacto::Bezier bezier{{
        {100, 300},
        {200, 100},
        {300, 500},
        {400, 300},
    }};
    xml = toXml(bezier);
    xml.toFile("res/bezier.xml");
    xml.fromFile("res/bezier.xml");
    bezier = cacto::toBezier(xml);

    cacto::Rectangle rectangle{{100, 10}, {100, 100}};
    xml = toXml(rectangle);
    xml.toFile("res/rectangle.xml");
    xml.fromFile("res/rectangle.xml");
    rectangle = cacto::toRectangle(xml);

    cacto::Ellipse ellipse{{200, 200}, {100, 50}};
    xml = toXml(ellipse);
    xml.toFile("res/ellipse.xml");
    xml.fromFile("res/ellipse.xml");
    ellipse = cacto::toEllipse(xml);

    cacto::Triangle triangle{{300, 300}, {400, 350}, {350, 400}};
    xml = toXml(triangle);
    xml.toFile("res/triangle.xml");
    xml.fromFile("res/triangle.xml");
    triangle = cacto::toTriangle(xml);

    cacto::LineViewer viewer{};
    sf::VertexArray array{};

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
        viewer.setPrecision(5);
        viewer.setColor(sf::Color::Green);
        viewer.setClosed(false);
        window.draw(viewer);

        viewer.setLine(&rectangle);
        viewer.setPrecision(1);
        viewer.setColor(sf::Color::Blue);
        viewer.setClosed(true);
        window.draw(viewer);

        viewer.setLine(&ellipse);
        viewer.setPrecision(5);
        viewer.setColor(sf::Color::Yellow);
        viewer.setClosed(true);
        window.draw(viewer);

        viewer.setLine(&triangle);
        viewer.setPrecision(1);
        viewer.setColor(sf::Color::Cyan);
        viewer.setClosed(true);
        window.draw(viewer);

        window.draw(array);

        window.display();
    }

    return 0;
}