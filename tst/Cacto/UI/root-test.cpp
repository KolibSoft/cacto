#include <limits>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Core/Loader.hpp>
#include <Cacto/Graphics/Ellipse.hpp>
#include <Cacto/UI/Surface.hpp>
#include <Cacto/UI/Layout.hpp>
#include <Cacto/UI/AnchorLayout.hpp>
#include <Cacto/UI/Label.hpp>
#include <Cacto/UI/Button.hpp>
#include <Cacto/UI/Input.hpp>
#include <Cacto/UI/Picture.hpp>
#include <Cacto/UI/RowLayout.hpp>
#include <Cacto/UI/ColumnLayout.hpp>
#include <Cacto/UI/UIRoot.hpp>

auto _ = false;

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    sf::Font font;
    _ = font.loadFromFile("./res/Grandview.ttf");

    sf::Texture texture;
    _ = texture.loadFromFile("res/fondo.png");

    auto background = cacto::Surface::Rectangle;
    background.setColor(sf::Color::Red);

    cacto::Picture picture{texture, cacto::Picture::Fit};
    auto bgPicture = background;
    bgPicture.setColor(sf::Color::Cyan);
    picture.setBackground(&bgPicture);
    picture.setFixedHeight(200);
    picture.setMargin(10);
    picture.setPadding(10);
    picture.setHorizontalAnchor(cacto::Box::Center);
    picture.setVerticalAnchor(cacto::Box::Center);

    cacto::Label label{font, "LABEL"};
    auto bgLabel = background;
    bgLabel.setColor(sf::Color::Blue);
    label.setBackground(&bgLabel);
    label.setMaxWidth(0);
    label.setMaxHeight(0);
    label.setMargin(10);
    label.setPadding(10);

    cacto::Input input{font, "INPUT"};
    auto bgInput = background;
    bgInput.setColor(sf::Color::Green);
    input.setBackground(&bgInput);
    input.setMaxWidth(0);
    input.setMaxHeight(0);
    input.setMargin(10);
    input.setPadding(10);

    cacto::Button button{font, "BUTTON"};
    auto bgButton = background;
    bgButton.setColor(sf::Color::Magenta);
    button.setBackground(&bgButton);
    button.setMaxWidth(0);
    button.setMaxHeight(0);
    button.setMargin(10);
    button.setPadding(10);
    button.setOnClickListener([](auto &target, auto &event)
                              { std::cout << "Clicked\n"; });

    cacto::ColumnLayout column{};
    column.setBackground(&background);
    column.setMargin(10);
    column.setPadding(10);
    column.setDirection(cacto::Layout::Reverse);

    column.append(picture);
    column.setHorizontalAnchor(picture, cacto::Box::Start);
    column.setVerticalWeight(picture, 0.125);

    column.append(label);
    column.setHorizontalAnchor(label, cacto::Box::Start);
    column.setVerticalWeight(label, 0.125);

    column.append(input);
    column.setHorizontalAnchor(input, cacto::Box::Center);
    column.setVerticalWeight(input, 0.25);

    column.append(button);
    column.setHorizontalAnchor(button, cacto::Box::End);
    column.setVerticalWeight(button, 0.50);

    cacto::UIRoot root{};
    root.append(column);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (!root.event(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::Resized)
                    window.setView(sf::View(sf::FloatRect{{0, 0}, {sf::Vector2f(event.size.width, event.size.height)}}));
            }
        }
        root.compact();
        root.inflate(sf::Vector2f(sf::Mouse::getPosition(window)));
        root.place();
        window.clear(sf::Color::Black);
        window.draw(root);
        window.display();
    }

    return 0;
}