#include <limits>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Core/Loader.hpp>
#include <Cacto/Graphics/Ellipse.hpp>
#include <Cacto/UI/Picture.hpp>

auto _ = false;

enum Textures
{
    SurfaceTexture
};

cacto::Loader<sf::Texture> textures;

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    textures.setLoadFromFile(SurfaceTexture, "res/fondo.png");
    auto texture = textures.get(SurfaceTexture);
    texture->setRepeated(true);

    cacto::Picture root{*texture.get()};
    auto background = cacto::colorSurface(sf::Color::Red);
    root.setBackground(&background);
    root.setMargin(10);
    root.setPadding(10);
    root.getFigure().setScale(cacto::Figure::Crop);
    root.getFigure().setHorizontalAnchor(cacto::Box::Center);
    root.getFigure().setVerticalAnchor(cacto::Box::Center);

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