#include <cmath>
#include <SFML/Graphics/Rect.hpp>
#include <Cacto/Graphics/VectorUtils.hpp>
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

    const sf::Vector2f Ellipse::getCenter() const
    {
        return {m_centerX, m_centerY};
    }

    void Ellipse::setCenter(const sf::Vector2f &value)
    {
        m_centerX = value.x;
        m_centerY = value.y;
        m_left = m_centerX - m_radiusX;
        m_right = m_centerX + m_radiusX;
        m_top = m_centerY - m_radiusY;
        m_bottom = m_centerY + m_radiusY;
    }

    const sf::Vector2f Ellipse::getDiameters() const
    {
        return {m_radiusX * 2, m_radiusY * 2};
    }

    void Ellipse::setDiameters(const sf::Vector2f &value)
    {
        m_radiusX = value.x / 2;
        m_radiusY = value.y / 2;
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

    Ellipse::~Ellipse() = default;

    const Ellipse Ellipse::Identity{{0, 0}, {1, 1}};

    XmlValue toXml(const Ellipse &ellipse)
    {
        XmlValue xml{"Ellipse", {}};
        auto center = ellipse.getCenter();
        auto diameters = ellipse.getDiameters();
        xml["center"] = toString(center);
        xml["diameters"] = toString(diameters);
        return std::move(xml);
    }

    void fromXml(Ellipse &ellipse, const XmlValue &xml)
    {
        ellipse = {};
        sf::Vector2f center{};
        sf::Vector2f diameters{};
        fromString(center, xml.getAttribute("center", "0,0"));
        fromString(diameters, xml.getAttribute("diameters", "0,0"));
        ellipse.setCenter(center);
        ellipse.setDiameters(diameters);
    }

    namespace ellipse
    {

        XmlValue XmlConverter::toXml(const Geometry *const value) const
        {
            const Ellipse *ellipse = nullptr;
            if (value && typeid(*value) == typeid(Ellipse) && (ellipse = dynamic_cast<const Ellipse *>(value)))
            {
                auto xml = cacto::toXml(*ellipse);
                return std::move(xml);
            }
            return nullptr;
        }

        Geometry *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.isTag() && xml.getName() == "Ellipse")
            {
                auto ellipse = std::make_shared<Ellipse>();
                cacto::fromXml(*ellipse, xml);
                Line::XmlStack.push(ellipse);
                Geometry::XmlStack.push(ellipse);
                return ellipse.get();
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}