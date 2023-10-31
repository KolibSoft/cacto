#include <limits>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/Ellipse.hpp>
#include <Cacto/UI/Surface.hpp>
#include <Cacto/UI/Block.hpp>
#include <Cacto/UI/VirtualLayout.hpp>
#include <Cacto/UI/Button.hpp>

auto _ = false;

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    sf::Font font;
    auto _ = font.loadFromFile("./res/Grandview.ttf");

    auto background = cacto::Surface::Rectangle;
    background.setColor(sf::Color::Red);

    cacto::VirtualLayout root{};
    root.setBackground(&background);
    root.setMargin(10);
    root.setPadding(10);

    cacto::Button button{font, "It Works"};
    auto bgBlock = background;
    bgBlock.setColor(sf::Color::Blue);
    button.getBlock().setBackground(&bgBlock);
    button.getBlock().setMargin(10);
    button.getBlock().setFixedWidth(0);
    button.getBlock().setFixedHeight(0);
    button.getBlock().setPadding(10);

    button.setOnClickListener([](auto &node, auto &event)
                              { std::cout << "Clicked\n"; });

    root.append(button);
    root.setHorizontalAnchor(button, cacto::Block::Center);
    root.setVerticalAnchor(button, cacto::Block::Center);
    // root.setMinWidth(300);
    // root.setMinHeight(300);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (!root.event(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::Resized)
                    window.setView(sf::View(sf::FloatRect{{0, 0}, {sf::Vector2f(event.size.width, event.size.height)}}));
            }
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