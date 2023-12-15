#include <limits>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/Ellipse.hpp>
#include <Cacto/Graphics/TexturePack.hpp>
#include <Cacto/Lang/Utils.hpp>
#include <Cacto/UI/Surface.hpp>

int main()
{

    cacto::TexturePack pack{"res"};

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");
    auto root = cacto::colorSurface(sf::Color::White);

    root.setTexture(cacto::getTexture("fondo.png"))
        .setTextureRect({{-100, -100}, {1000, 1000}});

    // cacto::toXmlFile(root, "res/surface.xml", 2);
    cacto::fromXmlFile(root, "res/surface.xml");

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