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

    auto span = std::make_shared<cacto::Span>();
    (*span).setFont(cacto::getFont("res/Grandview.ttf"));
    auto &text = span->asText();
    auto bounds = text.getLocalBounds();
    text.setString("My Span Text");
    text.setOrigin({bounds.width / 2, bounds.height / 2});
    text.setRotation(sf::degrees(45));
    text.setStyle(sf::Text::Bold | sf::Text::Italic | sf::Text::StrikeThrough);
    text.setOutlineThickness(10);
    text.setOutlineColor(sf::Color::Blue);

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
        window.draw(*span);
        window.display();
    }

    return 0;
}