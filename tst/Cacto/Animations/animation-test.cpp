#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/Skeleton.hpp>
#include <Cacto/Graphics/Mesh.hpp>
#include <Cacto/Graphics/TexturePack.hpp>
#include <Cacto/Graphics/GeometryPack.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Animations/Linear.hpp>
#include <Cacto/Animations/Coloring.hpp>
#include <Cacto/UI/Surface.hpp>
#include <Cacto/Lang/Utils.hpp>

int main()
{

    cacto::TexturePack textures{"."};
    cacto::GeometryPack geometries{"."};

    std::cout << "Node Converters: " << cacto::XmlConverter<cacto::Node>::getConverterCount() << '\n';

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    cacto::Skeleton skeleton{};
    cacto::fromXmlFile(skeleton, "res/skeleton.xml");
    std::cout << cacto::toXml(skeleton).toString() << "\n";
    cacto::toXmlFile(skeleton, "res/skeleton.xml", 2);

    auto left = skeleton.firstDescendant<cacto::Skeleton>("left");
    auto left_mesh = dynamic_cast<cacto::Mesh *>(left->getChild());
    auto right = skeleton.firstDescendant<cacto::Skeleton>("right");
    auto right_mesh = dynamic_cast<cacto::Mesh *>(right->getChild());
    auto surface = skeleton.firstDescendant<cacto::Surface>("surface");
    surface->setWidth(100);
    surface->setHeight(100);

    cacto::Linear linear{1, 2, sf::Time::Zero, sf::seconds(5), cacto::Animation::Forward, cacto::Animation::Flip};
    cacto::Coloring coloring{sf::Color::Red, sf::Color::Blue, sf::Time::Zero, sf::seconds(5), cacto::Animation::Reverse, cacto::Animation::Flip};
    sf::Time lifetime{};

    sf::Clock clock{};
    clock.start();
    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
                skeleton.asTransformable().setPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
            else if (event.type == sf::Event::MouseWheelScrolled)
            {
                skeleton.asTransformable().rotate(sf::degrees(event.mouseWheelScroll.delta));
                skeleton.asTransformable().setScale(skeleton.asTransformable().getScale() + sf::Vector2f{event.mouseWheelScroll.delta / 100, -event.mouseWheelScroll.delta / 100});
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                    left->asTransformable().rotate(sf::degrees(5));
                else if (event.key.code == sf::Keyboard::Right)
                    right->asTransformable().rotate(sf::degrees(5));
            }
        }

        auto dt = clock.restart();
        lifetime += dt;

        auto f = linear.getValue(lifetime);
        auto c = coloring.getValue(lifetime);
        skeleton.asTransformable().setScale({f, f});
        cacto::setColor(left_mesh->asArray(), c);
        cacto::setColor(right_mesh->asArray(), c);

        window.clear();
        window.draw(skeleton);
        window.display();
    }

    return 0;
}