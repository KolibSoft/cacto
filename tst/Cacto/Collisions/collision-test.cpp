#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/DrawNode.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Graphics/Rectangle.hpp>
#include <Cacto/Collisions/Body.hpp>
#include <Cacto/Collisions/CollisionNode.hpp>
#include <Cacto/Collisions/Dimension.hpp>
#include <Cacto/Common/GenericNode.hpp>

class Buddy
    : public cacto::Body,
      public virtual cacto::CollisionNode,
      public virtual cacto::DrawNode
{

public:
    mutable sf::VertexArray visual{sf::PrimitiveType::LineStrip};

    bool onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override
    {
        cacto::setPoints(visual, *getGeometry());
        cacto::setColor(visual, sf::Color::Red);
        visual.append(visual[0]);
        auto _states = states;
        _states.transform *= getTransform();
        target.draw(visual, _states);
        return false;
    }

    bool onCollision(cacto::Dimension &dimension) override
    {
        dimension.collisions(*this);
        return false;
    }

    void collision(Body &body) override
    {
        std::cout << "Collision detected\n";
    }

    Buddy()
    {
        setGeometry(std::make_shared<cacto::Rectangle>(cacto::Rectangle({0, 0}, {50, 50})));
        setOrigin({25, 25});
    }
};

auto makeSolid(const sf::Vector2f &position)
{
    auto solid = std::make_shared<Buddy>();
    solid->setPosition(position);
    return solid;
}

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    cacto::GenericNode root;
    root.append(makeSolid({100, 100}));
    root.append(makeSolid({200, 100}));
    root.append(makeSolid({200, 200}));
    root.append(makeSolid({100, 200}));

    auto dynamic = std::make_shared<Buddy>();
    root.append(dynamic);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::Resized)
                window.setView(sf::View(sf::FloatRect({0, 0}, sf::Vector2f{float(event.size.width), float(event.size.height)})));
        }

        cacto::Dimension dimension{sf::FloatRect{{0, 0}, sf::Vector2f(window.getSize())}};
        cacto::CollisionNode::collision(root, dimension);

        dynamic->setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
        window.clear(sf::Color::Black);
        window.draw(dimension);
        window.draw(root);
        window.display();
    }

    return 0;
}