#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/DrawNode.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Graphics/Ellipse.hpp>
#include <Cacto/Collisions/Body.hpp>
#include <Cacto/Collisions/CollisionNode.hpp>
#include <Cacto/Collisions/Dimension.hpp>
#include <Cacto/Common/GenericNode.hpp>

auto color = sf::Color::Black;

class Buddy
    : public sf::Transformable,
      public virtual cacto::Body,
      public virtual cacto::CollisionNode,
      public virtual cacto::DrawNode
{

public:
    mutable sf::VertexArray visual{sf::PrimitiveType::LineStrip};
    mutable cacto::SharedGeometry geometry{new cacto::Ellipse({0, 0}, {25, 25})};
    mutable cacto::Trace trace{geometry, getInverseTransform()};

    cacto::Trace getTrace() const override
    {
        return {geometry, getTransform()};
    }

    bool onCollision(cacto::Dimension &dimension) override
    {
        trace = getTrace();
        auto &target = dimension.locateCollisions(*this, trace);
        target.append(*this, trace);
        return false;
    }

    bool onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override
    {
        cacto::setPoints(visual, *geometry);
        cacto::setColor(visual, sf::Color::Red);
        visual.append(visual[0]);
        auto _states = states;
        _states.transform *= getTransform();
        target.draw(visual, _states);
        return false;
    }

    void collision(Body &body) override
    {
        color = sf::Color::White;
    }

    Buddy()
    {
        setScale({2, 1});
        setRotation(sf::degrees(30));
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
    window.setFramerateLimit(60);

    cacto::GenericNode root;
    root.append(makeSolid({100, 50}));
    root.append(makeSolid({250, 100}));
    root.append(makeSolid({475, 325}));
    root.append(makeSolid({100, 225}));

    auto dynamic = std::make_shared<Buddy>();
    root.append(dynamic);

    cacto::Dimension dimension{sf::FloatRect{{0, 0}, sf::Vector2f(window.getSize())}};

    sf::Clock clock;
    clock.start();
    auto frames = 0;
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

        color = sf::Color::Black;
        dimension.clean();
        cacto::CollisionNode::collision(root, dimension);

        dynamic->setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
        window.clear(color);
        window.draw(dimension);
        window.display();
        auto dt = clock.restart();
        if ((frames += 1) % 100 == 0)
        {
            frames = 0;
            std::cout << "FPS: " << (1 / dt.asSeconds()) << "\n";
        }
    }

    return 0;
}