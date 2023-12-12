#include <stdexcept>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
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

    f32t Rectangle::getLeft() const
    {
        return m_left;
    }

    void Rectangle::setLeft(f32t value)
    {
        m_left = value;
        m_right = value + m_width;
    }

    f32t Rectangle::getTop() const
    {
        return m_top;
    }

    void Rectangle::setTop(f32t value)
    {
        m_top = value;
        m_bottom = value + m_height;
    }

    f32t Rectangle::getWidth() const
    {
        return m_width;
    }

    void Rectangle::setWidth(f32t value)
    {
        m_width = value;
        m_right = m_left + value;
    }

    f32t Rectangle::getHeight() const
    {
        return m_height;
    }

    void Rectangle::setHeight(f32t value)
    {
        m_height = value;
        m_bottom = m_left + value;
    }

    Rectangle::Rectangle(const sf::Vector2f &position, const sf::Vector2f &size)
        : m_left(position.x), m_top(position.y),
          m_width(size.x), m_height(size.y),
          m_right(position.x + size.x), m_bottom(position.y + size.y)
    {
    }

    Rectangle::~Rectangle() = default;

    Rectangle Rectangle::Identity{{0, 0}, {1, 1}};

    namespace rectangle
    {

        JsonValue JsonConverter::toJson(const Geometry *const value) const
        {
            const Rectangle *rectangle = nullptr;
            if (value && (rectangle = dynamic_cast<const Rectangle *>(value)))
            {
                auto json = JsonValue::ObjectValue;
                json["$type"] = "Rectangle";
                json["position"] = {rectangle->getLeft(), rectangle->getTop()};
                json["size"] = {rectangle->getWidth(), rectangle->getHeight()};
                return std::move(json);
            }
            return nullptr;
        }

        Geometry *JsonConverter::fromJson(const JsonValue &json) const
        {
            if (json.isObject() && json["$type"] == "Rectangle")
            {
                auto rectangle = new Rectangle();
                auto &position = json["position"];
                auto &size = json["size"];
                rectangle->setLeft(f32t(position[0].getNumber()));
                rectangle->setTop(f32t(position[1].getNumber()));
                rectangle->setWidth(f32t(size[0].getNumber()));
                rectangle->setHeight(f32t(size[1].getNumber()));
                return rectangle;
            }
            return nullptr;
        }

        JsonConverter Converter{};

    }

}