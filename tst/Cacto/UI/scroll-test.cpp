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
#include <Cacto/UI/ScrollLayout.hpp>
#include <Cacto/UI/Button.hpp>

auto _ = false;

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    sf::Font font;
    auto _ = font.loadFromFile("./res/Grandview.ttf");

    auto background = cacto::Surface::Rectangle;
    background.setColor(sf::Color::Red);

    cacto::ScrollLayout root{};
    root.setBackground(&background);
    root.setMargin(10);
    root.setPadding(10);

    cacto::Button button{font, "It Works"};
    auto bgBlock = background;
    bgBlock.setColor(sf::Color::Blue);
    button.setBackground(&bgBlock);
    button.setMargin(10);
    button.setFixedWidth(400);
    button.setFixedHeight(400);
    button.setPadding(10);
    button.setHorizontalAnchor(cacto::Box::Center);
    button.setVerticalAnchor(cacto::Box::Center);

    button.setOnClickListener([](auto &node, auto &event)
                              { std::cout << "Clicked\n"; });

    root.append(button);
    root.setHorizontalAnchor(cacto::Block::Center);
    root.setVerticalAnchor(cacto::Block::Center);

    root.setFixedWidth(300);
    root.setFixedHeight(300);

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
        // root.inflate(sf::Vector2f{sf::Mouse::getPosition(window)});
        root.inflate(sf::Vector2f{window.getSize()});
        root.place();
        window.clear(sf::Color::Black);
        window.draw(root);
        window.display();
    }

    return 0;
}