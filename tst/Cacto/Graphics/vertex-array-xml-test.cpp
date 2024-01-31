#include <vector>
#include <fstream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Graphics/ColorPack.hpp>
#include <Cacto/Graphics/VertexArrayUtils.hpp>

int main()
{

    cacto::ColorPack pack("res/colors.json");

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");
    sf::VertexArray array{};
    cacto::XmlValue xml{};

    std::ifstream istream{"res/vertex_array.xml"};
    istream >> xml;
    array = cacto::toVertexArray(xml);

    std::ofstream ostream{"res/vertex_array.xml"};
    xml = cacto::toXml(array);
    ostream << xml;

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(array);
        window.display();
    }

    return 0;
}