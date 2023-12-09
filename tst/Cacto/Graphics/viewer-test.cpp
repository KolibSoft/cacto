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
#include <Cacto/Graphics/Utils.hpp>

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    cacto::Straight straight{{10, 10}, {100, 200}};
    straight.toFile("res/lines/straight.json");
    straight.fromFile("res/lines/straight.json");

    cacto::Bezier bezier{{
        {100, 300},
        {200, 100},
        {300, 500},
        {400, 300},
    }};
    bezier.toFile("res/lines/bezier.json");
    bezier.fromFile("res/lines/bezier.json");

    cacto::Rectangle rectangle{{100, 10}, {100, 100}};
    rectangle.toFile("res/geometries/rectangle.json");
    rectangle.fromFile("res/geometries/rectangle.json");

    cacto::Ellipse ellipse{{200, 200}, {100, 50}};
    ellipse.toFile("res/geometries/ellipse.json");
    ellipse.fromFile("res/geometries/ellipse.json");

    cacto::Triangle triangle{{300, 300}, {400, 350}, {350, 400}};
    triangle.toFile("res/geometries/triangle.json");
    triangle.fromFile("res/geometries/triangle.json");

    cacto::LineViewer viewer{};

    cacto::JsonValue json = nullptr;
    json.fromFile("res/vertex_array.json");
    json.toFile("res/vertex_array.json");
    sf::VertexArray array{};
    cacto::vertexArrayFromJson(array, json);

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

        window.draw(array);

        window.display();
    }

    return 0;
}