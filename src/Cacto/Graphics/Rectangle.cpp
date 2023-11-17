#include <stdexcept>
#include <Cacto/Graphics/Rectangle.hpp>

namespace cacto
{

    std::size_t Rectangle::getPointCount() const
    {
        return 4;
    }

    sf::Vector2f Rectangle::getPoint(std::size_t index, std::size_t precision) const
    {
        if (precision < 1)
            precision = 1;
        index %= 4 * precision;
        if (index < precision)
            return sf::Vector2f(m_left + (m_width / precision) * index, m_top);
        index -= precision;
        if (index < precision)
            return sf::Vector2f(m_right, m_top + (m_height / precision) * index);
        index -= precision;
        if (index < precision)
            return sf::Vector2f(m_right - (m_width / precision) * index, m_bottom);
        index -= precision;
        if (index < precision)
            return sf::Vector2f(m_left, m_bottom - (m_height / precision) * index);
        throw std::runtime_error("Broken code");
    }

    sf::FloatRect Rectangle::getBounds() const
    {
        auto bounds = sf::FloatRect({m_left, m_top}, {m_right - m_left, m_bottom - m_top});
        return bounds;
    }

    bool Rectangle::containsPoint(const sf::Vector2f &point) const
    {
        auto result = (point.x >= m_left &&
                       point.x <= m_right &&
                       point.y >= m_top &&
                       point.y <= m_bottom);
        return result;
    }

    JsonValue Rectangle::toJson() const
    {
        auto json = JsonValue::ObjectValue;
        json["type"] = "Rectangle";
        json["position"] = {f64t(m_left), f64t(m_top)};
        json["size"] = {f64t(m_width), f64t(m_height)};
        return json;
    }

    void Rectangle::fromJson(const JsonValue &json)
    {
        auto &position = json["position"];
        auto &size = json["size"];
        m_left = f32t(position[0].asNumber());
        m_top = f32t(position[1].asNumber());
        m_width = f32t(size[0].asNumber());
        m_height = f32t(size[1].asNumber());
        m_right = m_left + m_width;
        m_bottom = m_top + m_bottom;
    }

    Rectangle::Rectangle(const sf::Vector2f &position, const sf::Vector2f &size)
        : m_left(position.x), m_top(position.y),
          m_width(size.x), m_height(size.y),
          m_right(position.x + size.x), m_bottom(position.y + size.y)
    {
    }

    Rectangle::~Rectangle()
    {
    }

    Rectangle Rectangle::Identity{{0, 0}, {1, 1}};

}