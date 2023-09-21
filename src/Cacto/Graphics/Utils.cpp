#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Cacto/Graphics/Utils.hpp>

namespace cacto
{

    void setPositions(sf::Vertex *const vertexes, const sf::Vector2f *positions, szt count)
    {
        for (szt i = 0; i < count; i++)
        {
            vertexes[i].position = positions[i];
        }
    }

    void setPositions(sf::VertexArray &array, const std::vector<sf::Vector2f> &positions)
    {
        auto count = positions.size();
        array.resize(count);
        auto *vertexes = &(array[0]);
        auto *_points = &(positions[0]);
        setPositions(vertexes, _points, count);
    }

    void setColor(sf::Vertex *const vertexes, const sf::Color &color, szt count)
    {
        for (szt i = 0; i < count; i++)
        {
            vertexes[i].color = color;
        }
    }

    void setColor(sf::VertexArray &array, const sf::Color &color)
    {
        auto count = array.getVertexCount();
        auto *vertexes = &(array[0]);
        setColor(vertexes, color, count);
    }

    void setTexCoords(sf::Vertex *const vertexes, const sf::FloatRect bounds, const sf::FloatRect texRect, szt count)
    {
        for (szt i = 0; i < count; i++)
        {
            auto &position = vertexes[i].position;
            auto &texCoords = vertexes[i].texCoords;
            texCoords.x = (position.x - bounds.left) * (texRect.width / bounds.width) + texRect.left;
            texCoords.y = (position.y - bounds.top) * (texRect.height / bounds.height) + texRect.top;
        }
    }

    void setTexCoords(sf::VertexArray &array, const sf::FloatRect texRect)
    {
        auto count = array.getVertexCount();
        auto *vertexes = &(array[0]);
        auto bounds = array.getBounds();
        setTexCoords(vertexes, bounds, texRect, count);
    }

    void mapPositions(sf::Vertex *const vertexes, const sf::FloatRect bounds, const sf::FloatRect surface, szt count)
    {
        for (szt i = 0; i < count; i++)
        {
            auto &position = vertexes[i].position;
            position.x = (position.x - bounds.left) * (surface.width / bounds.width) + surface.left;
            position.y = (position.y - bounds.top) * (surface.height / bounds.height) + surface.top;
        }
    }

    void mapPositions(sf::VertexArray &array, const sf::FloatRect surface)
    {
        auto count = array.getVertexCount();
        auto *vertexes = &(array[0]);
        auto bounds = array.getBounds();
        mapPositions(vertexes, bounds, surface, count);
    }

    bool zoneIn(const sf::FloatRect &rect, const sf::FloatRect &zone)
    {
        auto rectLeft = std::min(rect.left, rect.left + rect.width);
        auto rectTop = std::min(rect.top, rect.top + rect.height);
        auto rectRight = std::max(rect.left, rect.left + rect.width);
        auto rectBottom = std::max(rect.top, rect.top + rect.height);

        auto zoneLeft = std::min(zone.left, zone.left + zone.width);
        auto zoneTop = std::min(zone.top, zone.top + zone.height);
        auto zoneRight = std::max(zone.left, zone.left + zone.width);
        auto zoneBottom = std::max(zone.top, zone.top + zone.height);

        auto result = rectLeft <= zoneLeft && rectTop <= zoneTop && rectRight >= zoneRight && rectBottom >= zoneBottom;
        return result;
    }

    bool zoneWith(const sf::FloatRect &rect, const sf::FloatRect &zone)
    {
        auto rectLeft = std::min(rect.left, rect.left + rect.width);
        auto rectTop = std::min(rect.top, rect.top + rect.height);
        auto rectRight = std::max(rect.left, rect.left + rect.width);
        auto rectBottom = std::max(rect.top, rect.top + rect.height);

        auto zoneLeft = std::min(zone.left, zone.left + zone.width);
        auto zoneTop = std::min(zone.top, zone.top + zone.height);
        auto zoneRight = std::max(zone.left, zone.left + zone.width);
        auto zoneBottom = std::max(zone.top, zone.top + zone.height);

        auto result = rectLeft <= zoneRight && rectTop <= zoneBottom && rectRight >= zoneLeft && rectBottom >= zoneTop;
        return result;
    }

}