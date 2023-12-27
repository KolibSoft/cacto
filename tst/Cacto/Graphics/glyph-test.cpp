#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/Utils.hpp>

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    sf::Font font;
    auto _ = font.loadFromFile("res/font.ttf");

    sf::VertexArray array(sf::PrimitiveType::Triangles);
    cacto::setGlyphs(array, font, "It Works AV", cacto::TextDirection::ToTop, 32, false, 0);
    cacto::setColor(array, sf::Color::Red);

    sf::Transformable transformable{};

    sf::Text text{font, "It Works AV", 32};

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        transformable.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));

        window.clear();

        window.draw(text);

        auto states = sf::RenderStates::Default;
        states.transform = transformable.getTransform();
        states.texture = &font.getTexture(32);
        window.draw(array, states);

        window.display();
    }

    return 0;
}