#include <cmath>
#include <Cacto/Graphics/Ellipse.hpp>

namespace cacto
{

    std::size_t Ellipse::getPointCount() const
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

    JsonValue Ellipse::toJson() const
    {
        auto json = JsonValue::ObjectValue;
        json["type"] = "Ellipse";
        json["center"] = {f64t(m_centerX), f64t(m_centerY)};
        json["diameters"] = {f64t(m_radiusX * 2), f64t(m_radiusY * 2)};
        return json;
    }

    void Ellipse::fromJson(const JsonValue &json)
    {
        auto &center = json["center"];
        auto &diameters = json["diameters"];
        m_centerX = f32t(center[0].asNumber());
        m_centerY = f32t(center[1].asNumber());
        m_radiusX = f32t(diameters[0].asNumber() / 2);
        m_radiusY = f32t(diameters[1].asNumber() / 2);
        m_left = m_centerX - m_radiusX;
        m_right = m_centerX + m_radiusX;
        m_top = m_centerY - m_radiusY;
        m_bottom = m_centerY + m_radiusY;
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