#include <limits>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/Ellipse.hpp>
#include <Cacto/Window/EventNode.hpp>
#include <Cacto/UI/Surface.hpp>
#include <Cacto/UI/FrameLayout.hpp>

auto _ = false;

class Frame
    : public cacto::FrameLayout,
      public virtual cacto::EventNode
{

public:
    cacto::EventListener onClickListener;
    cacto::Surface background{cacto::Surface::Rectangle};

    bool onBubble(Node &target, const sf::Event &event)
    {
        if (event.type == sf::Event::MouseButtonReleased && onClickListener)
        {
            onClickListener(target, event);
            return true;
        }
        else
        {
            auto handled = bubbleParent(target, event);
            return handled;
        }
    }

    Frame()
    {
        setBackground(&background);
    }
};

class Square
    : public cacto::Block,
      public virtual cacto::EventNode
{

public:
    cacto::EventListener onClickListener;
    cacto::Surface background{cacto::Surface::Rectangle};

    Square()
    {
        background.setColor(sf::Color::Cyan);
        setBackground(&background);
        setFixedWidth(100);
        setFixedHeight(100);
    }

protected:
    bool onEvent(const sf::Event &event) override
    {
        if (eventChildren(event))
            return true;
        else if (event.type == sf::Event::MouseButtonReleased && contains({float(event.mouseButton.x), float(event.mouseButton.y)}))
        {
            if (onClickListener)
                onClickListener(*this, event);
            else
                bubbleParent(*this, event);
            return true;
        }
        return false;
    }
};

auto makeFrame(const sf::Color &color, cacto::Node &node, cacto::Box::Anchor hAnchor, cacto::Box::Anchor vAnchor)
{
    Frame frame{};
    frame.background.setColor(color);
    frame.append(node);
    frame.setHorizontalAnchor(hAnchor);
    frame.setVerticalAnchor(vAnchor);
    frame.setMargin(10);
    frame.setPadding(10);
    return frame;
}

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    Square target{};
    auto level1 = makeFrame(sf::Color::Green, target, cacto::Box::Center, cacto::Box::Center);
    auto level2 = makeFrame(sf::Color::Blue, level1, cacto::Box::Center, cacto::Box::Center);
    level2.setMaxWidth(0);
    level2.setMaxHeight(0);
    auto root = makeFrame(sf::Color::Red, level2, cacto::Box::Center, cacto::Box::Center);

    root.onClickListener = [](auto &target, auto &event)
    {
        std::cout << "Clicked Bubbled!!!\n";
    };

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (!cacto::EventNode::event(root, event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::Resized)
                    window.setView(sf::View(sf::FloatRect{{0, 0}, {sf::Vector2f(event.size.width, event.size.height)}}));
            }
        }
        root.compact();
        root.inflate(sf::Vector2f{sf::Mouse::getPosition(window)});
        root.place();
        window.clear(sf::Color::Black);
        window.draw(root);
        window.display();
    }

    return 0;
}