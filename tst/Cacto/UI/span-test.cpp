#include <limits>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/FontPack.hpp>
#include <Cacto/UI/Surface.hpp>
#include <Cacto/UI/Span.hpp>

auto _ = false;

int main()
{

    cacto::FontPack fonts{"."};

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    sf::Font font;
    auto _ = font.loadFromFile("./res/Grandview.ttf");

    auto span = std::make_shared<cacto::Span>();
    auto bounds = span->getLocalBounds();
    (*span).setFont(cacto::getFont("res/Grandview.ttf"));
    (*span).setString("My Span Text");
    (*span).setOrigin({bounds.width / 2, bounds.height / 2});
    (*span).setRotation(sf::degrees(45));
    (*span).setStyle(sf::Text::Bold | sf::Text::Italic | sf::Text::StrikeThrough);
    (*span).setOutlineThickness(10);
    (*span).setOutlineColor(sf::Color::Blue);

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
        span->compact();
        span->inflate();
        span->place();
        window.clear(sf::Color::Black);
        window.draw((sf::Text &)*span);
        window.display();
    }

    return 0;
}