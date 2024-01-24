#include <algorithm>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

int main()
{

    std::vector<std::shared_ptr<sf::RenderWindow>> windows{};
    windows.push_back(std::make_shared<sf::RenderWindow>(sf::VideoMode({640, 468}), "SFML Window 1"));
    windows.push_back(std::make_shared<sf::RenderWindow>(sf::VideoMode({640, 468}), "SFML Window 2"));

    while (windows.size())
    {
        for (auto &window : windows)
            if (window->isOpen())
            {
                sf::Event event{};
                while (window->pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window->close();
                }
                window->clear();
                window->display();
            }
        windows.erase(std::remove_if(windows.begin(),
                                     windows.end(),
                                     [](auto &window)
                                     { return !window->isOpen(); }),
                      windows.end());
    }

    return 0;
}