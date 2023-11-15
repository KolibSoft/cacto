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
#include <Cacto/UI/RowLayout.hpp>

class Layout
    : public cacto::RowLayout,
      public virtual cacto::EventNode
{

public:
    Node *focusedNode{};

    Layout() {}
    virtual ~Layout() {}

protected:
    bool onBubble(Node &target, const sf::Event &event) override
    {
        if (event.type == sf::Event::GainedFocus)
        {
            if (focusedNode && focusedNode != &target)
            {
                auto focusable = dynamic_cast<cacto::Focusable *>(focusedNode);
                focusable->unfocus();
            }
            focusedNode = &target;
        }
        auto handled = bubbleParent(target, event);
        return handled;
    }
};

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    sf::Font font;
    auto _ = font.loadFromFile("./res/Grandview.ttf");

    auto background = cacto::Surface::Rectangle;
    background.setColor(sf::Color::Red);

    cacto::Label label{font, "LABEL"};
    auto bgLabel = background;
    bgLabel.setColor(sf::Color::Blue);
    label.setBackground(&bgLabel);
    label.setMargin(10);
    label.setPadding(10);

    cacto::Input input{font, "INPUT"};
    auto bgInput = background;
    bgInput.setColor(sf::Color::Green);
    input.setBackground(&bgInput);
    input.setMargin(10);
    input.setPadding(10);

    cacto::Button button{font, "BUTTON"};
    auto bgButton = background;
    bgButton.setColor(sf::Color::Magenta);
    button.setBackground(&bgButton);
    button.setMargin(10);
    button.setPadding(10);
    button.setOnClickListener([](auto &target, auto &event)
                              { std::cout << "Clicked\n"; });

    Layout root{};
    root.setBackground(&background);
    root.setMargin(10);
    root.setPadding(10);
    root.setDirection(cacto::RowLayout::Reverse);

    root.append(label);
    root.setVerticalAnchor(label, cacto::Box::Start);
    root.setVerticalWeight(label, 0.5);
    root.setHorizontalWeight(label, 0.25);

    root.append(input);
    root.setVerticalAnchor(input, cacto::Box::Center);
    root.setHorizontalWeight(input, 0.25);

    root.append(button);
    root.setVerticalAnchor(button, cacto::Box::End);
    root.setHorizontalWeight(button, 0.50);

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