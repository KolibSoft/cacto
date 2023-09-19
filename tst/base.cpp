#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Core/GenericNode.hpp>
#include <Cacto/Graphics/DrawSignal.hpp>
#include <Cacto/Graphics/DrawNode.hpp>

class Square
    : public cacto::GenericNode,
      public cacto::DrawNode
{

public:
    sf::RectangleShape shape;

    bool dispatchSignal(cacto::Node *const target, const cacto::Signal &signal) override
    {
        auto handled = DrawNode::handleSignal(target, signal) || Node::dispatchSignal(target, signal);
        return handled;
    }

protected:
    void onDraw(const cacto::DrawSignal &signal) override
    {
        auto &target = signal.target;
        auto states = signal.states;
        target.draw(shape, states);
        states.transform *= shape.getTransform();
        Node::dispatchSignal(nullptr, cacto::DrawSignal{target, states});
    }
};

auto makeSquare(const sf::Color &color, const sf::FloatRect &rect)
{
    auto square = std::make_shared<Square>();
    square->shape.setSize({rect.width, rect.height});
    square->shape.setPosition({rect.left, rect.top});
    square->shape.setFillColor(color);
    return square;
}

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");
    auto square = makeSquare(sf::Color::Red, {{10, 10}, {100, 100}});
    auto subsquare = makeSquare(sf::Color::Blue, {{10, 10}, {50, 50}});
    square->append(subsquare);

    square->shape.setOrigin({50, 50});
    square->shape.setRotation(sf::degrees(45));
    square->shape.move({100, 100});

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        square->dispatchSignal(nullptr, cacto::DrawSignal{window, sf::RenderStates::Default});
        window.display();
    }

    return 0;
}