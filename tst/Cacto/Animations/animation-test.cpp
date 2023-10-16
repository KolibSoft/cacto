#include <math.h>
#include <iostream>
#include <functional>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Core/LeafNode.hpp>
#include <Cacto/Graphics/DrawNode.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Graphics/Ellipse.hpp>
#include <Cacto/Collisions/Body.hpp>
#include <Cacto/Collisions/CollisionNode.hpp>
#include <Cacto/Collisions/Dimension.hpp>
#include <Cacto/Common/GenericNode.hpp>

#include <Cacto/Graphics/Straight.hpp>
#include <Cacto/Graphics/Bezier.hpp>
#include <Cacto/Graphics/Rectangle.hpp>

#include <Cacto/Animations/Animation.hpp>
#include <Cacto/Animations/Linear.hpp>
#include <Cacto/Animations/Coloring.hpp>

auto color = sf::Color::Black;
using Movement = std::function<sf::Vector2f(const sf::Time &lifetime)>;

class Buddy
    : public sf::Transformable,
      public virtual cacto::LeafNode,
      public virtual cacto::Body,
      public virtual cacto::CollisionNode,
      public virtual cacto::DrawNode,
      public virtual cacto::UpdateNode
{

public:
    mutable sf::VertexArray visual{sf::PrimitiveType::TriangleFan};
    mutable cacto::SharedGeometry geometry{new cacto::Ellipse({0, 0}, {25, 25})};
    mutable cacto::Trace trace{};
    mutable sf::Color color{};

    sf::Time lifetime;
    Movement movement;
    cacto::Linear<sf::Vector2f> scaleAnimation;
    cacto::Coloring colorAnimation;

    cacto::SharedNode getParent() const override
    {
        auto parent = m_parent.lock();
        return parent;
    }

    void onUpdate(const sf::Time &time) override
    {
        lifetime += time;
        if (movement)
        {
            auto position = movement(lifetime);
            setPosition(position);
            updateChildren(time);
        }
        auto scale = scaleAnimation.getValue(lifetime);
        setScale(scale);
        color = colorAnimation.getValue(lifetime);
        if (lifetime > sf::seconds(20))
            lifetime = sf::Time::Zero;
    }

    void onCollision(cacto::Dimension &dimension, const sf::Transform &transform) override
    {
        trace = {geometry, transform * getTransform()};
        auto &target = dimension.locateCollisions(*this, trace);
        target.append(*this, trace);
        collisionChildren(dimension, transform);
    }

    void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override
    {
        cacto::setPoints(visual, *geometry);
        cacto::setColor(visual, color);
        // visual.append(visual[0]);
        auto _states = states;
        _states.transform *= getTransform();
        target.draw(visual, _states);
        drawChildren(target, _states);
    }

    void collision(Body &body) override
    {
        color = sf::Color::White;
    }

    Buddy()
    {
        setScale({2, 1});
        setRotation(sf::degrees(30));
        scaleAnimation.setFrom({1, 2});
        scaleAnimation.setTo({2, 1});
        scaleAnimation.setDuration(sf::seconds(10));
        colorAnimation.setFrom(sf::Color::Red);
        colorAnimation.setTo(sf::Color::Green);
        colorAnimation.setDuration(sf::seconds(10));
    }

protected:
    void onAttach(const cacto::SharedNode &parent) override
    {
        m_parent = parent;
    }

    void onDetach(const cacto::SharedNode &parent) override
    {
        m_parent.reset();
    }

private:
    cacto::WeakNode m_parent;
};

auto makeSolid(const sf::Vector2f &position, const Movement &movement)
{
    auto solid = std::make_shared<Buddy>();
    solid->setPosition(position);
    solid->movement = movement;
    return solid;
}

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");
    window.setFramerateLimit(120);

    cacto::Straight straight{{0, 0}, {300, 300}};
    cacto::Rectangle geometry{{100, 100}, {300, 300}};
    cacto::Bezier bezier{{
        {100, 300},
        {300, 100},
        {500, 500},
        {700, 300},
    }};

    cacto::Animation animation;
    animation.setDelay(sf::seconds(5));
    animation.setDuration(sf::seconds(10));

    auto precision = 120 * 10;
    auto straightMovement = [&](const sf::Time &lifetime) -> sf::Vector2f
    {
        auto index = animation.getIndex(lifetime, precision);
        auto position = straight.getPoint(index, precision / straight.getSideCount());
        return position;
    };
    auto geometryMovement = [&](const sf::Time &lifetime) -> sf::Vector2f
    {
        auto index = animation.getIndex(lifetime, precision);
        auto position = geometry.getPoint(index, precision / geometry.getSideCount());
        return position;
    };
    auto bezierMovement = [&](const sf::Time &lifetime) -> sf::Vector2f
    {
        auto index = animation.getIndex(lifetime, precision);
        auto position = bezier.getPoint(index, precision / bezier.getSideCount());
        return position;
    };

    auto root = std::make_shared<cacto::GenericNode>();
    root->append(makeSolid({100, 50}, nullptr));
    root->append(makeSolid({250, 100}, straightMovement));
    root->append(makeSolid({475, 225}, geometryMovement));
    root->append(makeSolid({100, 225}, bezierMovement));

    auto dynamic = std::make_shared<Buddy>();
    root->append(dynamic);

    cacto::Dimension dimension{sf::FloatRect{{0, 0}, sf::Vector2f(window.getSize())}, 4};

    sf::VertexArray path(sf::PrimitiveType::LineStrip);

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

        auto dt = clock.restart();
        cacto::UpdateNode::update(*root, dt);

        color = sf::Color::Black;
        dimension.clean();
        cacto::CollisionNode::collision(*root, dimension);

        dynamic->setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
        window.clear(color);

        cacto::setPoints(path, straight, precision);
        cacto::setColor(path, sf::Color::Green);
        window.draw(path);

        cacto::setPoints(path, geometry, precision);
        cacto::setColor(path, sf::Color::Green);
        window.draw(path);

        cacto::setPoints(path, bezier, precision);
        cacto::setColor(path, sf::Color::Green);
        window.draw(path);

        window.draw(*root);
        window.draw(dimension);

        window.display();

        if ((frames += 1) % 100 == 0)
        {
            frames = 0;
            std::cout << "FPS: " << (1 / dt.asSeconds()) << "\n";
        }
    }

    return 0;
}