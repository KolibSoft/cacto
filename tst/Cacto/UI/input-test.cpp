#include <limits>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Core/Loader.hpp>
#include <Cacto/Graphics/Ellipse.hpp>
#include <Cacto/UI/Surface.hpp>
#include <Cacto/UI/Input.hpp>

auto _ = false;

enum Textures
{
    SurfaceTexture
};

cacto::Loader<sf::Texture> textures;

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    sf::Font font;
    auto _ = font.loadFromFile("./res/Grandview.ttf");

    auto background = cacto::Surface::Rectangle;
    background.setColor(sf::Color::Red);

    cacto::Input root{font};
    root.getBlock().setBackground(&background);
    root.getBlock().setMargin(10);
    root.getSpan().setOutlineThickness(10);
    root.getSpan().setOutlineColor(sf::Color::Blue);
    root.setHorizontalAnchor(cacto::Box::Center);
    root.setVerticalAnchor(cacto::Box::Center);
    root.setOnInputListener([](cacto::Node &target, const sf::Event &event)
                            { std::cout << "Text entered\n"; });

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
        root.inflate(sf::Vector2f(sf::Mouse::getPosition(window)));
        root.place();
        window.clear(sf::Color::Black);
        window.draw(root);
        window.display();
    }

    return 0;
}