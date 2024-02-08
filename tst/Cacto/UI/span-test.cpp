#include <limits>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Core/StringPack.hpp>
#include <Cacto/Graphics/FontPack.hpp>
#include <Cacto/Graphics/ColorPack.hpp>
#include <Cacto/UI/Surface.hpp>
#include <Cacto/UI/Span.hpp>

auto _ = false;

int main()
{

    cacto::StringPack strings{"res/strings.json"};
    cacto::ColorPack colors{"res/colors.json"};
    cacto::FontPack fonts{"."};

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    auto span = cacto::Span()
                    .setFont(cacto::getResource<sf::Font>("res/font.ttf"))
                    .setString("My Span Text")
                    .setDirection(cacto::TextDirection::ToBottom)
                    .setCharacterSize(16)
                    .setColor(sf::Color::Cyan);

    cacto::XmlValue xml = nullptr;

    xml.fromFile("res/span.xml");
    span = cacto::toSpan(xml);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::Resized)
                window.setView(sf::View(sf::FloatRect{{0, 0}, {sf::Vector2f(event.size.width, event.size.height)}}));
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                xml.fromFile("res/span.xml");
                span = cacto::toSpan(xml);
            }
        }
        span.compact();
        span.inflate();
        span.place();
        window.clear();
        window.draw(span);
        window.display();
    }

    xml = cacto::toXml(span);
    xml.toFile("res/span.xml");

    return 0;
}