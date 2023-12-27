#include <stdexcept>
#include <cmath>
#include <SFML/Graphics/Rect.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Graphics/Triangle.hpp>

namespace cacto
{

    f32t triangle_sign(const sf::Vector2f &p1, const sf::Vector2f &p2, const sf::Vector2f &p3)
    {
        return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
    }

    std::size_t Triangle::getPointCount() const
    {
        return 3;
    }

    sf::Vector2f Triangle::getPoint(std::size_t index, std::size_t precision) const
    {
        if (precision < 1)
            precision = 1;
        index %= 3 * precision;
        if (index < precision)
            return sf::Vector2f(m_pointA + float(index) * (m_pointB - m_pointA) / float(precision));
        index -= precision;
        if (index < precision)
            return sf::Vector2f(m_pointB + float(index) * (m_pointC - m_pointB) / float(precision));
        index -= precision;
        if (index < precision)
            return sf::Vector2f(m_pointC + float(index) * (m_pointA - m_pointC) / float(precision));
        throw std::runtime_error("Broken code");
    }

    sf::FloatRect Triangle::getBounds() const
    {
        auto bounds = sf::FloatRect({m_left, m_top}, {m_right - m_left, m_bottom - m_top});
        return bounds;
    }

    bool Triangle::containsPoint(const sf::Vector2f &point) const
    {
        if (point.x >= m_left && point.x <= m_right &&
            point.y >= m_top && point.y <= m_bottom)
        {
            auto s1 = triangle_sign(point, m_pointA, m_pointB);
            auto s2 = triangle_sign(point, m_pointB, m_pointC);
            auto s3 = triangle_sign(point, m_pointC, m_pointA);
            auto result = !(((s1 < 0) || (s2 < 0) || (s3 < 0)) &&
                            ((s1 > 0) || (s2 > 0) || (s3 > 0)));
            return result;
        }
        return false;
    }

    const sf::Vector2f &Triangle::getPointA() const
    {
        return m_pointA;
    }

    void Triangle::setPointA(const sf::Vector2f &value)
    {
        m_pointA = value;
        m_left = std::min(m_pointA.x, std::min(m_pointB.x, m_pointC.x));
        m_right = std::max(m_pointA.x, std::max(m_pointB.x, m_pointC.x));
        m_top = std::min(m_pointA.y, std::min(m_pointB.y, m_pointC.y));
        m_bottom = std::max(m_pointA.y, std::max(m_pointB.y, m_pointC.y));
    }

    const sf::Vector2f &Triangle::getPointB() const
    {
        return m_pointB;
    }

    void Triangle::setPointB(const sf::Vector2f &value)
    {
        m_pointB = value;
        m_left = std::min(m_pointA.x, std::min(m_pointB.x, m_pointC.x));
        m_right = std::max(m_pointA.x, std::max(m_pointB.x, m_pointC.x));
        m_top = std::min(m_pointA.y, std::min(m_pointB.y, m_pointC.y));
        m_bottom = std::max(m_pointA.y, std::max(m_pointB.y, m_pointC.y));
    }

    const sf::Vector2f &Triangle::getPointC() const
    {
        return m_pointC;
    }

    void Triangle::setPointC(const sf::Vector2f &value)
    {
        m_pointC = value;
        m_left = std::min(m_pointA.x, std::min(m_pointB.x, m_pointC.x));
        m_right = std::max(m_pointA.x, std::max(m_pointB.x, m_pointC.x));
        m_top = std::min(m_pointA.y, std::min(m_pointB.y, m_pointC.y));
        m_bottom = std::max(m_pointA.y, std::max(m_pointB.y, m_pointC.y));
    }

    Triangle::Triangle(const sf::Vector2f &pointA, const sf::Vector2f &pointB, const sf::Vector2f &pointC)
        : m_pointA(pointA), m_pointB(pointB), m_pointC(pointC),
          m_left(std::min(pointA.x, std::min(pointB.x, pointC.x))), m_top(std::min(pointA.y, std::min(pointB.y, pointC.y))),
          m_right(std::max(pointA.x, std::max(pointB.x, pointC.x))), m_bottom(std::max(pointA.y, std::max(pointB.y, pointC.y)))
    {
    }

    Triangle::~Triangle() = default;

    XmlValue toXml(const Triangle &triangle)
    {
        XmlValue xml{"Triangle", {}};
        auto pointA = triangle.getPointA();
        auto pointB = triangle.getPointB();
        auto pointC = triangle.getPointC();
        xml["pointA"] = toString(pointA);
        xml["pointB"] = toString(pointB);
        xml["pointC"] = toString(pointC);
        return std::move(xml);
    }

    void fromXml(Triangle &triangle, const XmlValue &xml)
    {
        triangle = {};
        sf::Vector2f pointA{};
        sf::Vector2f pointB{};
        sf::Vector2f pointC{};
        fromString(pointA, xml.getAttribute("pointA", "0,0"));
        fromString(pointB, xml.getAttribute("pointB", "0,0"));
        fromString(pointC, xml.getAttribute("pointC", "0,0"));
        triangle.setPointA(pointA);
        triangle.setPointB(pointB);
        triangle.setPointC(pointC);
    }

    namespace triangle
    {

        XmlValue XmlConverter::toXml(const Geometry *const value) const
        {
            const Triangle *triangle = nullptr;
            if (value && typeid(*value) == typeid(Triangle) && (triangle = dynamic_cast<const Triangle *>(value)))
            {
                auto xml = cacto::toXml(*triangle);
                return std::move(xml);
            }
            return nullptr;
        }

        Geometry *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.isTag() && xml.getName() == "Triangle")
            {
                auto triangle = new Triangle();
                cacto::fromXml(*triangle, xml);
                return triangle;
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}