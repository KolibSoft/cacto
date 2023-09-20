#include <iostream>
#include <functional>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Common/GenericNode.hpp>
#include <Cacto/Graphics/DrawSignal.hpp>
#include <Cacto/Window/EventSignal.hpp>
#include <Cacto/Animations/UpdateSignal.hpp>

class Square : public cacto::GenericNode
{

public:
    std::string tag;
    sf::RectangleShape shape;
    std::function<bool(Node *const target, const cacto::EventSignal &)> onEventListener;
    sf::Vector2f velocity;

protected:
    bool onUpdate(Node *const target, const cacto::UpdateSignal &signal) override
    {
        if (target == nullptr || target == this)
        {
            shape.move({velocity.x * signal.time.asSeconds(),
                        velocity.y * signal.time.asSeconds()});
        }
        return false;
    }

    bool onDraw(Node *const target, const cacto::DrawSignal &signal) override
    {
        if (target == nullptr || target == this)
        {
            auto states = signal.states;
            signal.target.draw(shape, states);
            states.transform *= shape.getTransform();
            Node::dispatchSignal(cacto::DrawSignal{signal.target, states});
            return true;
        }
        return false;
    }

    bool onEvent(Node *const target, const cacto::EventSignal &signal) override
    {
        auto handled = onEventListener && onEventListener(target ? target : this, signal);
        return handled;
    }
};

auto makeSquare(const sf::Color &color, const sf::FloatRect &rect, const std::string &tag, const sf::Vector2f &velocity)
{
    auto square = std::make_shared<Square>();
    square->tag = tag;
    square->shape.setSize({rect.width, rect.height});
    square->shape.setPosition({rect.left, rect.top});
    square->shape.setFillColor(color);
    square->velocity = velocity;
    auto toggle = true;
    square->onEventListener = [=](auto *target, auto &signal) mutable
    {
        if (signal.event.type == sf::Event::MouseButtonReleased)
        {
            auto *node = dynamic_cast<Square *>(target);
            if (node && toggle)
            {
                toggle = false;
                std::cout << "Event captured: " << node->tag << "\n";
                return true;
            }
        }
        return false;
    };
    return square;
}

auto makeEntity(const sf::Vector2f &position)
{
    auto square = makeSquare(sf::Color::Red, {{10, 10}, {100, 100}}, "RED", {10, 0});
    square->append(makeSquare(sf::Color::Blue, {{10, 10}, {50, 50}}, "BLUE", {10, 0}));
    square->getChild()->append(makeSquare(sf::Color::Green, {{10, 10}, {25, 25}}, "GREEN", {10, 0}));
    square->shape.setPosition(position);
    square->shape.setOrigin({50, 50});
    square->shape.setRotation(sf::degrees(45));
    square->shape.move({100, 100});
    return square;
}

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");
    auto root = std::make_shared<cacto::GenericNode>();
    root->append(makeEntity({0, 0}));
    root->append(makeEntity({-10, 10}));
    root->append(makeEntity({-20, 20}));
    root->append(makeEntity({-30, 30}));
    root->append(makeEntity({-40, 40}));
    root->append(makeEntity({-50, 50}));

    sf::Clock clock;
    clock.start();
    auto frames = 0;
    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            root->dispatchSignal(cacto::EventSignal{event});
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        auto dt = clock.restart();
        root->dispatchSignal(cacto::UpdateSignal{dt});
        root->dispatchSignal(cacto::DrawSignal{window, sf::RenderStates::Default});
        window.display();
        if ((frames += 1) % 100 == 0)
        {
            frames = 0;
            std::cout << "FPS: " << (1 / dt.asSeconds()) << "\n";
        }
    }

    return 0;
}