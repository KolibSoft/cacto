#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/Skeleton.hpp>
#include <Cacto/Graphics/Mesh.hpp>
#include <Cacto/Graphics/TexturePack.hpp>
#include <Cacto/Graphics/FontPack.hpp>
#include <Cacto/Graphics/GeometryPack.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Animations/Linear.hpp>
#include <Cacto/Animations/Coloring.hpp>
#include <Cacto/Animations/AnimationPack.hpp>
#include <Cacto/UI/Surface.hpp>
#include <Cacto/UI/Button.hpp>
#include <Cacto/Lang/Utils.hpp>

int main()
{

    std::cout << "Label size: " << sizeof(cacto::Label) << '\n';
    std::cout << "Text size: " << sizeof(sf::Text) << '\n';

    cacto::TexturePack textures{"."};
    cacto::GeometryPack geometries{"."};
    cacto::FontPack fonts{"."};
    cacto::AnimationPack animations{"."};

    std::cout << "Node Converters: " << cacto::XmlConverter<cacto::Node>::getConverterCount() << '\n';

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");
    window.setFramerateLimit(60);

    cacto::Skeleton skeleton{};
    cacto::fromXmlFile(skeleton, "res/composed.xml");
    std::cout << cacto::toXml(skeleton).toString() << "\n";
    cacto::toXmlFile(skeleton, "res/composed.xml", 2);

    auto left = skeleton.firstDescendant<cacto::Skeleton>("left");
    auto left_mesh = dynamic_cast<cacto::Mesh *>(left->getChild());
    auto right = skeleton.firstDescendant<cacto::Skeleton>("right");
    auto right_mesh = dynamic_cast<cacto::Mesh *>(right->getChild());
    auto surface = skeleton.firstDescendant<cacto::Surface>("surface");
    auto button = skeleton.firstDescendant<cacto::Button>("button");

    button->setOnClickListener([&](cacto::Node &target, const sf::Event &event)
                               { std::cout << "Clicked\n"; });

    auto linear = dynamic_cast<const cacto::Linear *>(cacto::getAnimation("res/linear.xml"));
    auto coloring = dynamic_cast<const cacto::Coloring *>(cacto::getAnimation("res/coloring.xml"));
    sf::Time lifetime{};

    sf::Clock clock{};
    clock.start();
    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (cacto::EventNode::event(skeleton, event))
                break;
            else if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Right)
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
        // std::cout << "FPS: " << (1 / dt.asSeconds()) << '\n';
        lifetime += dt;

        auto f = linear->getValue(lifetime);
        auto c = coloring->getValue(lifetime);
        skeleton.asTransformable().setScale({f, f});
        cacto::setColor(left_mesh->asArray(), c);
        cacto::setColor(right_mesh->asArray(), c);

        cacto::InflatableNode::compact(skeleton);
        cacto::InflatableNode::inflate(skeleton);
        cacto::InflatableNode::place(skeleton);

        surface->asBox().setWidth(100);
        surface->asBox().setHeight(100);

        window.clear();
        window.draw(skeleton);
        window.display();
    }

    return 0;
}