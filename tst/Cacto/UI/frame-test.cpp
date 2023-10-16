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
};

class Square
    : public cacto::Block,
      public virtual cacto::EventNode
{

public:
    cacto::EventListener onClickListener;

    Square()
    {
        setBackground(cacto::makeColorSurface(sf::Color::Cyan));
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
    auto frame = std::make_shared<Frame>();
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

    auto target = std::make_shared<Square>();
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

    root->onClickListener = [](auto &target, auto &event)
    {
        std::cout << "Clicked Bubbled!!!\n";
    };

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (!cacto::EventNode::event(*root, event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::Resized)
                    window.setView(sf::View(sf::FloatRect{{0, 0}, {sf::Vector2f(event.size.width, event.size.height)}}));
            }
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