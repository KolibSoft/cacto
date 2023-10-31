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
#include <Cacto/UI/ColumnLayout.hpp>

class Layout
    : public cacto::ColumnLayout,
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
    label.getBlock().setBackground(&bgLabel);
    label.getBlock().setMaxWidth(0);
    label.getBlock().setMaxHeight(0);
    label.getBlock().setMargin(10);
    label.getBlock().setPadding(10);

    cacto::Input input{font, "INPUT"};
    auto bgInput = background;
    bgInput.setColor(sf::Color::Green);
    input.getBlock().setBackground(&bgInput);
    input.getBlock().setMaxWidth(0);
    input.getBlock().setMaxHeight(0);
    input.getBlock().setMargin(10);
    input.getBlock().setPadding(10);

    cacto::Button button{font, "BUTTON"};
    auto bgButton = background;
    bgButton.setColor(sf::Color::Magenta);
    button.getBlock().setBackground(&bgButton);
    button.getBlock().setMaxWidth(0);
    // button.getBlock().setMaxHeight(0);
    button.getBlock().setMargin(10);
    button.getBlock().setPadding(10);
    button.setOnClickListener([](auto &target, auto &event)
                              { std::cout << "Clicked\n"; });

    Layout root{};
    root.setBackground(&background);
    root.setMargin(10);
    root.setPadding(10);
    root.setDirection(cacto::Layout::Reverse);
    root.setVerticalAnchor(cacto::Box::End);

    root.append(label);
    root.setHorizontalAnchor(label, cacto::Box::Start);

    root.append(input);
    root.setHorizontalAnchor(input, cacto::Box::Center);

    root.append(button);
    root.setHorizontalAnchor(button, cacto::Box::End);

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