#include <fstream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Graphics/TransformableUtils.hpp>
#include <Cacto/Graphics/VertexArrayUtils.hpp>

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    sf::Font font;
    auto _ = font.loadFromFile("res/font.ttf");

    sf::VertexArray array(sf::PrimitiveType::Triangles);
    cacto::setGlyphs(array, "It Works AV", cacto::TextDirection::ToRight, font, 32, false, 0);
    cacto::setColor(array, sf::Color::Red);

    cacto::XmlValue xml = nullptr;
    sf::Transformable transformable{};
    sf::Text text{font, "It Works AV", 32};

    std::ifstream istream("res/transformable.xml");
    istream >> xml;
    transformable = cacto::toTransformable(xml);

    // std::ofstream ostream("res/transformable.xml");
    // xml = cacto::toXml(transformable);
    // ostream << xml;

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                std::ifstream istream("res/transformable.xml");
                istream >> xml;
                transformable = cacto::toTransformable(xml);
            }
        }

        window.clear();
        window.draw(text);

        auto states = sf::RenderStates::Default;
        states.transform = transformable.getTransform();
        states.texture = &font.getTexture(32);
        window.draw(array, states);

        window.display();
    }

    return 0;
}