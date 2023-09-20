#include <limits>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Common/GenericNode.hpp>
#include <Cacto/UI/InflatableNode.hpp>

class Surface
    : public cacto::GenericNode,
      public virtual cacto::InflatableNode
{

public:
    sf::RectangleShape shape{};
    float minWidth = 0;
    float minHeight = 0;
    float maxWidth = std::numeric_limits<float>::infinity();
    float maxHeight = std::numeric_limits<float>::infinity();

protected:
    bool onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override
    {
        target.draw(shape, states);
        return false;
    }

    sf::Vector2f onCompact(const sf::Vector2f &contentSize) override
    {
        shape.setSize({std::min(contentSize.x, minWidth),
                       std::min(contentSize.y, minHeight)});
        auto size = shape.getSize();
        return size;
    }

    sf::Vector2f onInflate(const sf::Vector2f &containerSize) override
    {
        shape.setSize({std::max(minWidth, std::min(containerSize.x, maxWidth)),
                       std::max(minHeight, std::min(containerSize.y, maxHeight))});
        auto size = shape.getSize();
        return size;
    }

    void onPlace(const sf::Vector2f &position) override
    {
        shape.setPosition(position);
    }
};

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");
    auto root = std::make_shared<Surface>();
    root->shape.setFillColor(sf::Color::Red);
    root->minWidth = 100;
    root->maxHeight = 100;

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
        root->compact();
        root->inflate(sf::Vector2f(sf::Mouse::getPosition(window)));
        root->place();
        window.clear(sf::Color::Black);
        window.draw(*root);
        window.display();
    }

    return 0;
}