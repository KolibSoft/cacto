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

auto color = sf::Color::Black;

class Buddy
    : public sf::Transformable,
      public virtual cacto::LeafNode,
      public virtual cacto::Body,
      public virtual cacto::CollisionNode,
      public virtual cacto::DrawNode,
      public virtual cacto::UpdateNode
{

public:
    mutable sf::VertexArray visual{sf::PrimitiveType::LineStrip};
    mutable cacto::SharedGeometry geometry{new cacto::Ellipse({0, 0}, {25, 25})};
    mutable cacto::Trace trace{};

    sf::Time lifetime;
    std::function<sf::Vector2f(const sf::Time &time)> movement;

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
        cacto::setColor(visual, sf::Color::Red);
        visual.append(visual[0]);
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

auto makeSolid(const sf::Vector2f &position)
{
    auto solid = std::make_shared<Buddy>();
    solid->setPosition(position);
    return solid;
}

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");
    window.setFramerateLimit(120);

    auto root = std::make_shared<cacto::GenericNode>();
    root->append(makeSolid({100, 50}));
    root->append(makeSolid({250, 100}));
    root->append(makeSolid({475, 225}));
    root->append(makeSolid({100, 225}));

    auto dynamic = std::make_shared<Buddy>();
    /*
    // Linear
    dynamic->movement = [](const sf::Time &time) -> sf::Vector2f
    {
        sf::Vector2f start{100, 100};
        sf::Vector2f end{200, 200};
        sf::Time t0 = sf::seconds(5);
        sf::Time tf = sf::seconds(10);
        sf::Time currentTime = time;
        if (currentTime < t0)
        {
            sf::Vector2f currentPosition = start;
            return currentPosition;
        }
        else if (currentTime >= tf)
        {
            sf::Vector2f currentPosition = end;
            return currentPosition;
        }
        else
        {
            float t = (currentTime - t0).asSeconds();
            sf::Vector2f currentPosition = start + (end - start) * (t / (tf - t0).asSeconds());
            return currentPosition;
        }
    };
    // Elliptic
    dynamic->movement = [](const sf::Time &time) -> sf::Vector2f
    {
        float a = 200;     // Semieje mayor
        float b = 100;     // Semieje menor
        float omega = 0.5; // Velocidad angular
        float t = time.asSeconds();

        float x = a * cos(omega * t);
        float y = b * sin(omega * t);

        sf::Vector2f point{400 + x, 300 + y};
        return point;
    };
    // Bezier
    dynamic->movement = [](const sf::Time &time) -> sf::Vector2f
    {
        float a = 0.1; // Coeficiente a de la parábola
        float b = 0.2; // Coeficiente b de la parábola
        float c = 0.3; // Coeficiente c de la parábola
        float t = time.asSeconds();

        float x = t;                     // Utilizamos el tiempo como coordenada x
        float y = a * x * x + b * x + c; // Ec. de la parábola

        sf::Vector2f point = {100 + x * 100, 500 - y * 100};
        return point;
    };
    // Complex
    dynamic->movement = [](const sf::Time &time) -> sf::Vector2f
    {
        sf::Vector2f p0{100, 300};
        sf::Vector2f p1{300, 100};
        sf::Vector2f p2{500, 500};
        sf::Vector2f p3{700, 300};
        auto t = time.asSeconds() / sf::seconds(10).asSeconds();

        if (t < 1.0)
        {
            float u = 1.0 - t;
            float tt = t * t;
            float uu = u * u;
            float uuu = uu * u;
            float ttt = tt * t;

            sf::Vector2f position = (uuu * p0) + (3 * uu * t * p1) + (3 * u * tt * p2) + (ttt * p3);

            return position;
        }

        return {0, 0};
    };
    */

    cacto::Straight straight{{0, 0}, {300, 300}};
    auto precision = 1200;

    // Straight
    dynamic->movement = [&](const sf::Time &time) -> sf::Vector2f
    {
        auto beginAt = sf::seconds(5);
        auto endAt = sf::seconds(15);
        auto index = 0;
        if (time < beginAt)
        {
            index = 0;
        }
        else if (time > endAt)
        {
            index = 1200 - 1;
        }
        else
        {
            auto duration = endAt - beginAt;
            index = int((time - beginAt) / duration * precision);
        }
        auto point = straight.getPoint(index, precision);
        return point;
    };

    cacto::Rectangle geometry{{100, 100}, {300, 300}};

    // Geometric
    dynamic->movement = [&](const sf::Time &time) -> sf::Vector2f
    {
        auto beginAt = sf::seconds(5);
        auto endAt = sf::seconds(15);
        auto index = 0;
        if (time < beginAt)
        {
            index = 0;
        }
        else if (time > endAt)
        {
            index = 1200 - 1;
        }
        else
        {
            auto duration = endAt - beginAt;
            index = int((time - beginAt) / duration * precision);
        }
        auto point = geometry.getPoint(index, precision / 4);
        return point;
    };

    cacto::Bezier bezier{{
        {100, 300},
        {300, 100},
        {500, 500},
        {700, 300},
    }};

    // Bezier
    dynamic->movement = [&](const sf::Time &time) -> sf::Vector2f
    {
        auto beginAt = sf::seconds(5);
        auto endAt = sf::seconds(15);
        auto index = 0;
        if (time < beginAt)
        {
            index = 0;
        }
        else if (time > endAt)
        {
            index = 1200 - 1;
        }
        else
        {
            auto duration = endAt - beginAt;
            index = int((time - beginAt) / duration * precision);
        }
        auto point = bezier.getPoint(index, precision);
        return point;
    };

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

        // dynamic->setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
        window.clear(color);

        // cacto::setPoints(path, straight, precision);
        // cacto::setColor(path, sf::Color::Green);
        window.draw(path);

        // cacto::setPoints(path, geometry, precision);
        // cacto::setColor(path, sf::Color::Green);
        window.draw(path);

        cacto::setPoints(path, bezier, precision);
        cacto::setColor(path, sf::Color::Green);
        window.draw(path);

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