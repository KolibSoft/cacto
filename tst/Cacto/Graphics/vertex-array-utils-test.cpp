#include <vector>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/VectorUtils.hpp>
#include <Cacto/Graphics/VertexArrayUtils.hpp>

auto makeSquare(const sf::Color &color, const sf::FloatRect &rect)
{
    std::vector<sf::Vector2f> points = {{rect.left, rect.top},
                                        {rect.left + rect.width, rect.top},
                                        {rect.left + rect.width, rect.top + rect.height},
                                        {rect.left, rect.top + rect.height}};
    sf::VertexArray array{sf::PrimitiveType::TriangleFan, 4};
    cacto::setPositions(&(array[0]), points.data(), points.size());
    cacto::setColor(array, color);
    cacto::mapPositions(array, rect);
    return array;
}

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");
    auto container = makeSquare(sf::Color::Red, {{10, 10}, {300, 200}});
    auto content = makeSquare(sf::Color::Blue, {{10, 10}, {100, 200}});

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        cacto::mapPositions(container, {{10, 10}, sf::Vector2f(sf::Mouse::getPosition(window))});
        auto scale = cacto::fitSize({content.getBounds().width, content.getBounds().height}, {container.getBounds().width, container.getBounds().height});
        cacto::mapPositions(content, {{10, 10}, scale});

        window.clear();
        window.draw(container);
        window.draw(content);
        window.display();
    }

    return 0;
}