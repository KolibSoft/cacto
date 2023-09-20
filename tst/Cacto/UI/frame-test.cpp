#include <limits>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/Ellipse.hpp>
#include <Cacto/UI/Surface.hpp>
#include <Cacto/UI/FrameLayout.hpp>

auto _ = false;

auto makeBlock(const sf::Color &color)
{
    auto block = std::make_shared<cacto::Block>();
    block->setBackground(cacto::makeColorSurface(color));
    block->setFixedWidth(100);
    block->setFixedHeight(100);
    return block;
}

auto makeFrame(const sf::Color &color, const cacto::SharedNode &node, cacto::Box::Anchor hAnchor, cacto::Box::Anchor vAnchor)
{
    auto frame = std::make_shared<cacto::FrameLayout>();
    frame->setBackground(cacto::makeColorSurface(color));
    frame->append(node);
    frame->setHorizontalAnchor(node, hAnchor);
    frame->setVerticalAnchor(node, vAnchor);
    frame->setMargin(10);
    frame->setPadding(10);
    return frame;
}

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    auto target = makeBlock(sf::Color::Yellow);
    auto root = makeFrame(
        sf::Color::Red,
        makeFrame(
            sf::Color::Blue,
            makeFrame(
                sf::Color::Green,
                target,
                cacto::Box::Center,
                cacto::Box::Center),
            cacto::Box::Start,
            cacto::Box::Start),
        cacto::Box::Start,
        cacto::Box::Start);

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
        if (target->contains(sf::Vector2f{sf::Mouse::getPosition(window)}))
        {
            std::cout << "It Works\n";
        }
        root->compact();
        root->inflate(sf::Vector2f{sf::Mouse::getPosition(window)});
        root->place();
        window.clear(sf::Color::Black);
        window.draw(*root);
        window.display();
    }

    return 0;
}