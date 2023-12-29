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
#include <Cacto/Graphics/VertexArrayUtils.hpp>
#include <Cacto/Window/NodeUtils.hpp>
#include <Cacto/Animations/Linear.hpp>
#include <Cacto/Animations/Coloring.hpp>
#include <Cacto/Animations/AnimationPack.hpp>
#include <Cacto/UI/Surface.hpp>
#include <Cacto/UI/Button.hpp>
#include <Cacto/UI/NodeUtils.hpp>
#include <Cacto/Lang/XmlValue.hpp>

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
    cacto::XmlValue xml = nullptr;
    xml.fromFile("res/composed.xml");
    cacto::fromXml(skeleton, xml);
    xml = cacto::toXml(skeleton);
    xml.toFile("res/composed.xml", 2);

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
            if (cacto::handle(skeleton, event))
                break;
            else if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Right)
                skeleton.setPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
            else if (event.type == sf::Event::MouseWheelScrolled)
            {
                skeleton.rotate(sf::degrees(event.mouseWheelScroll.delta));
                skeleton.setScale(skeleton.getScale() + sf::Vector2f{event.mouseWheelScroll.delta / 100, -event.mouseWheelScroll.delta / 100});
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                    left->rotate(sf::degrees(5));
                else if (event.key.code == sf::Keyboard::Right)
                    right->rotate(sf::degrees(5));
            }
        }

        auto dt = clock.restart();
        // std::cout << "FPS: " << (1 / dt.asSeconds()) << '\n';
        lifetime += dt;

        auto f = linear->getValue(lifetime);
        auto c = coloring->getValue(lifetime);
        skeleton.setScale({f, f});
        cacto::setColor(*left_mesh, c);
        cacto::setColor(*right_mesh, c);

        cacto::compact(skeleton);
        cacto::inflate(skeleton);
        cacto::place(skeleton);

        surface->setWidth(100);
        surface->setHeight(100);

        window.clear();
        window.draw(skeleton);
        window.display();
    }

    return 0;
}