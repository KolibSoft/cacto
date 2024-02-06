#pragma once

#include <utility>
#include <Cacto/Graphics/TileMap.hpp>

namespace cacto
{

    inline TileMap &&TileMap::setId(const std::string &value) &&
    {
        return std::move(setId(value));
    }

    inline TileMap &&TileMap::setTexture(const sf::Texture *const value) &&
    {
        return std::move(setTexture(value));
    }

    inline TileMap &&TileMap::setTileSize(const sf::Vector2f &value) &&
    {
        return std::move(setTileSize(value));
    }

    inline TileMap &&TileMap::setArea(const sf::IntRect &value) &&
    {
        return std::move(setArea(value));
    }

    inline TileMap &&TileMap::setTile(const sf::FloatRect &tile, const sf::Vector2i &position) &&
    {
        return std::move(setTile(tile, position));
    }

    inline TileMap &&TileMap::setTiles(const sf::FloatRect &tile, const sf::IntRect &area) &&
    {
        return std::move(setTiles(tile, area));
    }

    inline TileMap &&TileMap::fill(const sf::FloatRect &tile) &&
    {
        return std::move(fill(tile));
    }

}