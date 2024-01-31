#include <stdexcept>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <Cacto/Core/VectorUtils.hpp>
#include <Cacto/Graphics/VectorUtils.hpp>
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

    sf::Vector2f Rectangle::getPosition() const
    {
        return {m_left, m_top};
    }

    void Rectangle::setPosition(const sf::Vector2f &value)
    {
        m_left = value.x;
        m_right = value.x + m_width;
        m_top = value.y;
        m_bottom = value.y + m_height;
    }

    sf::Vector2f Rectangle::getSize() const
    {
        return {m_width, m_height};
    }

    void Rectangle::setSize(const sf::Vector2f &value)
    {
        m_width = value.x;
        m_right = m_left + value.x;
        m_height = value.y;
        m_bottom = m_left + value.y;
    }

    Rectangle::Rectangle(const sf::Vector2f &position, const sf::Vector2f &size)
        : m_left(position.x), m_top(position.y),
          m_width(size.x), m_height(size.y),
          m_right(position.x + size.x), m_bottom(position.y + size.y)
    {
    }

    Rectangle::~Rectangle() = default;

    const Rectangle Rectangle::Identity{{0, 0}, {1, 1}};

    XmlValue toXml(const Rectangle &rectangle)
    {
        XmlValue xml{"Rectangle", {}};
        auto position = rectangle.getPosition();
        auto size = rectangle.getSize();
        xml["position"] = toString(position);
        xml["size"] = toString(size);
        return std::move(xml);
    }

    Rectangle toRectangle(const XmlValue &xml)
    {
        Rectangle rectangle{};
        auto position = xml.getAttribute("position", "0,0");
        auto size = xml.getAttribute("size", "0,0");
        rectangle.setPosition(toVector(position));
        rectangle.setSize(toVector(size));
        return std::move(rectangle);
    }

    namespace rectangle
    {

        XmlValue XmlConverter::toXml(const Geometry *const value) const
        {
            const Rectangle *rectangle = nullptr;
            if (value && typeid(*value) == typeid(Rectangle) && (rectangle = dynamic_cast<const Rectangle *>(value)))
            {
                auto xml = cacto::toXml(*rectangle);
                return std::move(xml);
            }
            return nullptr;
        }

        Geometry *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.isTag() && xml.getName() == "Rectangle")
            {
                auto rectangle = new Rectangle();
                *rectangle = toRectangle(xml);
                return rectangle;
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}