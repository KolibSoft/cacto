#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Cacto/Graphics/TileMap.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Graphics/TexturePack.hpp>
#include <Cacto/Core/Utils.hpp>

int main()
{

    auto &pack = cacto::TexturePacks["tilemaps"] = {"res/textures"};
    
    sf::RenderWindow window(sf::VideoMode({640, 468}), "SFML Window");

    /*
    sf::Texture texture;
    auto _ = texture.loadFromFile("res/WallTile.png");
    pack.setTexture("tiles.png", texture);

    cacto::JsonValue json = nullptr;
    json.fromFile("res/rect_map.json");
    json.toFile("res/rect_map.json");

    std::unordered_map<std::string, sf::FloatRect> tiles{};
    for (auto &pair : json.asObject())
    {
        auto &tile = tiles[pair.first] = {};
        cacto::rectFromJson(tile, pair.second);
    }
    */
    cacto::TileMap tileMap{};
    /*
    tileMap.setTexture(&pack.getTexture("tiles.png"));
    tileMap.setTileSize({32, 32});
    tileMap.setArea({{1, 1}, {10, 10}});

    tileMap.setTiles({{1, 1}, {10, 1}}, tiles["HWall"]);
    tileMap.setTiles({{1, 10}, {10, 1}}, tiles["HWall"]);
    tileMap.setTiles({{1, 1}, {1, 10}}, tiles["VWall"]);
    tileMap.setTiles({{10, 1}, {1, 10}}, tiles["VWall"]);
    tileMap.setTile({1, 1}, tiles["TopLeft"]);
    tileMap.setTile({10, 1}, tiles["TopRight"]);
    tileMap.setTile({1, 10}, tiles["BottomLeft"]);
    tileMap.setTile({10, 10}, tiles["BottomRight"]);

    tileMap.toFile("res/tile_map.json");
    */
    tileMap.fromFile("res/tile_map.json");
    tileMap.toFile("res/tile_map.json");

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

    cacto::TexturePacks.clear();
    return 0;
}