#include <cmath>
#include <Cacto/Graphics/Ellipse.hpp>

namespace cacto
{

    std::size_t Ellipse::getSideCount() const
    {
        return 12;
    }

    sf::Vector2f Ellipse::getPoint(std::size_t index, std::size_t precision) const
    {
        if (precision < 1)
            precision = 1;
        auto count = 12 * precision;
        auto point = sf::Vector2f(
            m_centerX + m_radiusX * cosf((index * 2 * M_PI) / count),
            m_centerY + m_radiusY * sinf((index * 2 * M_PI) / count));
        return point;
    }

    sf::FloatRect Ellipse::getBounds() const
    {
        auto bounds = sf::FloatRect({m_left, m_top}, {m_right - m_left, m_bottom - m_top});
        return bounds;
    }

    bool Ellipse::containsPoint(const sf::Vector2f &point) const
    {
        if (
            point.x >= m_left && point.x <= m_right &&
            point.y >= m_top && point.y <= m_bottom)
        {
            auto dx = point.x - m_centerX;
            auto dy = point.y - m_centerY;
            auto result = ((dx * dx) / (m_radiusX * m_radiusX) +
                               (dy * dy) / (m_radiusY * m_radiusY) <=
                           1);
            return result;
        }
        return false;
    }

    Ellipse::Ellipse(const sf::Vector2f &center, const sf::Vector2f &diameters)
        : m_centerX(center.x), m_centerY(center.y),
          m_radiusX(diameters.x / 2), m_radiusY(diameters.y / 2),
          m_left(center.x - diameters.x / 2), m_top(center.y - diameters.y / 2),
          m_right(center.x + diameters.x / 2), m_bottom(center.y + diameters.y / 2)
    {
    }

    Ellipse::~Ellipse()
    {
    }

    Ellipse Ellipse::Identity{{0, 0}, {1, 1}};

}