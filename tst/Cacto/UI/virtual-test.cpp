#include <limits>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/Ellipse.hpp>
#include <Cacto/UI/Surface.hpp>
#include <Cacto/UI/Block.hpp>
#include <Cacto/UI/VirtualLayout.hpp>

auto _ = false;

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    auto background = cacto::Surface::Rectangle;
    background.setColor(sf::Color::Red);

    cacto::VirtualLayout root{};
    root.setBackground(&background);
    root.setMargin(10);
    root.setPadding(10);

    cacto::Block block{};
    auto bgBlock = background;
    bgBlock.setColor(sf::Color::Blue);
    block.setBackground(&bgBlock);
    block.setMargin(10);
    block.setMinWidth(100);
    block.setMaxHeight(100);
    block.setPadding(10);

    // root.append(block);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
                window.setView(sf::View(sf::FloatRect{{0, 0}, {sf::Vector2f(event.size.width, event.size.height)}}));
        }
        root.compact();
        root.inflate(sf::Vector2f{sf::Mouse::getPosition(window)});
        root.place();
        window.clear(sf::Color::Black);
        window.draw(root);
        window.display();
    }

    return 0;
}