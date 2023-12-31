#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Core/LeafNode.hpp>
#include <Cacto/Graphics/DrawNode.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Graphics/Ellipse.hpp>
#include <Cacto/Physics/Collisionable.hpp>
#include <Cacto/Physics/CollisionNode.hpp>
#include <Cacto/Physics/Dimension.hpp>
#include <Cacto/Physics/Trace.hpp>
#include <Cacto/Game/GameNode.hpp>

auto color = sf::Color::Black;

class Buddy
    : public sf::Transformable,
      public virtual cacto::LeafNode,
      public virtual cacto::Collisionable,
      public virtual cacto::CollisionNode,
      public virtual cacto::DrawNode
{

public:
    mutable sf::VertexArray visual{sf::PrimitiveType::LineStrip};
    mutable cacto::Ellipse *geometry{new cacto::Ellipse({0, 0}, {25, 25})};
    mutable cacto::Trace trace{*geometry};

    Node *const getParent() const override
    {
        return m_parent;
    }

    void onCollision(cacto::Dimension &dimension, const sf::Transform &transform) override
    {
        trace = {*geometry, transform * getTransform()};
        auto &target = dimension.locateCollisions(*this, trace);
        target.append(*this, trace);
        collisionChildren(dimension, transform);
    }

    void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override
    {
        cacto::setPoints(visual, *geometry);
        cacto::setColor(visual, sf::Color::Red);
        visual.append(visual[0]);
        auto _states = states;
        _states.transform *= getTransform();
        target.draw(visual, _states);
        drawChildren(target, _states);
    }

    void collision(Collisionable &body) override
    {
        color = sf::Color::White;
    }

    Buddy()
    {
        setScale({2, 1});
        setRotation(sf::degrees(30));
    }

protected:
    void onAttach(Node &parent) override
    {
        m_parent = &parent;
    }

    void onDetach(Node &parent) override
    {
        m_parent = nullptr;
    }

private:
    Node *m_parent{nullptr};
};

auto makeSolid(const sf::Vector2f &position)
{
    Buddy solid{};
    solid.setPosition(position);
    return solid;
}

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");
    window.setFramerateLimit(120);

    cacto::GameNode root{};
    auto buddy1 = makeSolid({100, 50});
    auto buddy2 = makeSolid({250, 100});
    auto buddy3 = makeSolid({475, 225});
    auto buddy4 = makeSolid({100, 225});

    root.append(buddy1);
    root.append(buddy2);
    root.append(buddy3);
    root.append(buddy4);

    Buddy dynamic{};
    root.append(dynamic);

    cacto::Dimension dimension{sf::FloatRect{{0, 0}, sf::Vector2f(window.getSize())}, 4};

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
            {
                sf::FloatRect rect{sf::FloatRect{{0, 0}, sf::Vector2f{float(event.size.width), float(event.size.height)}}};
                window.setView(sf::View(rect));
                dimension = {rect, 4};
            }
        }

        color = sf::Color::Black;
        dimension.clean();
        cacto::CollisionNode::collision(root, dimension);

        dynamic.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
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