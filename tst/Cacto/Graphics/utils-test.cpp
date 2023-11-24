#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Graphics/Rectangle.hpp>
#include <Cacto/Graphics/TexturePack.hpp>

auto makeSquare(const sf::Color &color, const sf::FloatRect &rect)
{
    sf::VertexArray array(sf::PrimitiveType::TriangleFan);
    cacto::setPoints(array, cacto::Rectangle::Identity);
    cacto::setColor(array, color);
    cacto::mapPositions(array, rect);
    return array;
}

int main()
{

    cacto::TexturePack pack{"res/textures"};

    // sf::Texture texture;
    // auto _ = texture.loadFromFile("res/fondo.png");
    // pack.setTexture("my_texture.png", texture);

    auto p = pack.getTexture("my_texture.png").getSize();

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