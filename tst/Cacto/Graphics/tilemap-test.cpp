#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Core/Loader.hpp>
#include <Cacto/Graphics/TileMap.hpp>

namespace R
{
    auto texture = cacto::Loader<sf::Texture>::fromFile("res/WallTile.png");
}

enum class Tile : int
{
    Pilar,
    Cross,
    HWall,
    VWall,
    Left,
    Right,
    Top,
    Bottom,
    TLeft,
    TRight,
    TTop,
    TBottom,
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight
};

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");
    auto texture = R::texture.get();

    std::map<Tile, sf::FloatRect> tiles;
    tiles[Tile::Pilar] = cacto::TileMap::createTile({0, 0}, {16, 16});
    tiles[Tile::Cross] = cacto::TileMap::createTile({1, 0}, {16, 16});
    tiles[Tile::HWall] = cacto::TileMap::createTile({2, 0}, {16, 16});
    tiles[Tile::VWall] = cacto::TileMap::createTile({3, 0}, {16, 16});
    tiles[Tile::Left] = cacto::TileMap::createTile({0, 1}, {16, 16});
    tiles[Tile::Right] = cacto::TileMap::createTile({1, 1}, {16, 16});
    tiles[Tile::Top] = cacto::TileMap::createTile({2, 1}, {16, 16});
    tiles[Tile::Bottom] = cacto::TileMap::createTile({3, 1}, {16, 16});
    tiles[Tile::TLeft] = cacto::TileMap::createTile({0, 2}, {16, 16});
    tiles[Tile::TRight] = cacto::TileMap::createTile({1, 2}, {16, 16});
    tiles[Tile::TTop] = cacto::TileMap::createTile({2, 2}, {16, 16});
    tiles[Tile::TBottom] = cacto::TileMap::createTile({3, 2}, {16, 16});
    tiles[Tile::TopLeft] = cacto::TileMap::createTile({0, 3}, {16, 16});
    tiles[Tile::TopRight] = cacto::TileMap::createTile({1, 3}, {16, 16});
    tiles[Tile::BottomLeft] = cacto::TileMap::createTile({2, 3}, {16, 16});
    tiles[Tile::BottomRight] = cacto::TileMap::createTile({3, 3}, {16, 16});

    cacto::TileMap tileMap{};
    tileMap.setTexture(texture.get());
    tileMap.setTileSize({32, 32});
    tileMap.setArea({{1, 1}, {10, 10}});

    tileMap.setTiles({{1, 1}, {10, 1}}, tiles[Tile::HWall]);
    tileMap.setTiles({{1, 10}, {10, 1}}, tiles[Tile::HWall]);
    tileMap.setTiles({{1, 1}, {1, 10}}, tiles[Tile::VWall]);
    tileMap.setTiles({{10, 1}, {1, 10}}, tiles[Tile::VWall]);
    tileMap.setTile({1, 1}, tiles[Tile::TopLeft]);
    tileMap.setTile({10, 1}, tiles[Tile::TopRight]);
    tileMap.setTile({1, 10}, tiles[Tile::BottomLeft]);
    tileMap.setTile({10, 10}, tiles[Tile::BottomRight]);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
                tileMap.setPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
        }
        window.clear();
        window.draw(tileMap);
        window.display();
    }

    return 0;
}