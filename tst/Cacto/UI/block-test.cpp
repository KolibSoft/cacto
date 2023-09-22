#include <limits>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/Ellipse.hpp>
#include <Cacto/UI/Surface.hpp>
#include <Cacto/UI/Block.hpp>

auto _ = false;

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    auto root = std::make_shared<cacto::Block>();
    root->setBackground(cacto::makeColorSurface(sf::Color::Red));
    root->setMargin(10);
    root->setMinWidth(100);
    root->setMaxHeight(100);
    root->setPadding(10);

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
        root->compact();
        root->inflate(sf::Vector2f{sf::Mouse::getPosition(window)});
        root->place();
        window.clear(sf::Color::Black);
        window.draw(*root);
        window.display();
    }

    return 0;
}