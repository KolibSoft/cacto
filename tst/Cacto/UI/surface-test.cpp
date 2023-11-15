#include <limits>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Core/Loader.hpp>
#include <Cacto/Graphics/Ellipse.hpp>
#include <Cacto/UI/Surface.hpp>
auto _ = false;

namespace R
{
    auto texture = cacto::Loader<sf::Texture>::fromFile("res/fondo.png");
}

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    auto texture = R::texture.get();
    texture->setRepeated(true);

    auto root = cacto::colorSurface(sf::Color::White);

    root.setTexture(texture.get())
        .setTextureRect({{-100, -100}, {1000, 1000}});

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
        root.inflate(sf::Vector2f(window.getSize()));
        root.place();
        window.clear(sf::Color::Black);
        window.draw(root);
        window.display();
    }

    return 0;
}