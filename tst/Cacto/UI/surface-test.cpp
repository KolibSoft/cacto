#include <limits>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/Ellipse.hpp>
#include <Cacto/UI/Surface.hpp>
auto _ = false;

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    auto texure = std::make_shared<sf::Texture>();
    _ = texure->loadFromFile("res/fondo.png");

    auto geometry = std::make_shared<cacto::Ellipse>(sf::Vector2f{0, 0}, sf::Vector2f{1, 1});

    auto root = cacto::makeTextureSurface(texure, geometry, 5);

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
        root->inflate(sf::Vector2f(window.getSize()));
        root->place();
        window.clear(sf::Color::Black);
        window.draw(*root);
        window.display();
    }

    return 0;
}