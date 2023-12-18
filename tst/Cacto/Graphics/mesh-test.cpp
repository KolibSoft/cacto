#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/Mesh.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Lang/Utils.hpp>

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    cacto::Node *node = nullptr;
    cacto::fromXmlFile(node, "res/mesh.xml");
    cacto::toXmlFile(node, "res/mesh.xml", 2);

    cacto::Mesh mesh{};
    cacto::fromXmlFile(mesh, "res/mesh.xml");
    std::cout << cacto::toXml(mesh).toString(2) << "\n";
    cacto::toXmlFile(mesh, "res/mesh.xml", 2);

    mesh.setPrimitiveType(sf::PrimitiveType::LineStrip);
    mesh.append(mesh[0]);
    sf::Transform transform = sf::Transform::Identity;
    // transform.scale({2, 2});
    // transform.rotate(sf::degrees(5));
    // transform.translate({10, 10});
    cacto::fromXmlFile(transform, "res/transform.xml");
    cacto::toXmlFile(transform, "res/transform.xml");
    auto matrix = transform.getMatrix();
    std::cout << std::fixed
              << matrix[0] << ' ' << matrix[1] << ' ' << matrix[2] << ' ' << matrix[3] << '\n'
              << matrix[4] << ' ' << matrix[5] << ' ' << matrix[6] << ' ' << matrix[7] << '\n'
              << matrix[8] << ' ' << matrix[9] << ' ' << matrix[10] << ' ' << matrix[11] << '\n'
              << matrix[12] << ' ' << matrix[13] << ' ' << matrix[14] << ' ' << matrix[15] << '\n';

    float values[9]{matrix[0], matrix[4], matrix[12],
                    matrix[1], matrix[5], matrix[13],
                    matrix[3], matrix[7], matrix[15]};

    sf::Transform recreated{matrix[0], matrix[4], matrix[12],
                            matrix[1], matrix[5], matrix[13],
                            matrix[3], matrix[7], matrix[15]};

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw((sf::VertexArray &)mesh, transform);
        window.draw((sf::VertexArray &)mesh, recreated);
        window.display();
    }

    return 0;
}