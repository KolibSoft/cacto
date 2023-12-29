#include <math.h>
#include <SFML/System/Vector2.hpp>
#include <Cacto/Graphics/VectorUtils.hpp>
#include <Cacto/Graphics/Bezier.hpp>

namespace cacto
{

    i32t binomialCoefficient(i32t n, i32t k)
    {
        if (k == 0 || k == n)
            return 1;
        auto coefficient = binomialCoefficient(n - 1, k - 1) + binomialCoefficient(n - 1, k);
        return coefficient;
    }

    szt Bezier::getPointCount() const
    {
        return m_points.size();
    }

    sf::Vector2f Bezier::getPoint(szt index, szt precision) const
    {
        if (precision < 1)
            precision = 1;
        index %= m_points.size() * precision;
        auto t = f32t(index) / f32t(m_points.size() * precision - 1);
        auto n = m_points.size() - 1;
        sf::Vector2f point{0, 0};
        for (int i = 0; i <= n; ++i)
        {
            f32t coeff = binomialCoefficient(n, i) * pow(1 - t, n - i) * pow(t, i);
            point += coeff * m_points[i];
        }
        return point;
    }

    const std::vector<sf::Vector2f> &Bezier::asPoints() const
    {
        return m_points;
    }

    std::vector<sf::Vector2f> &Bezier::asPoints()
    {
        return m_points;
    }

    Bezier::Bezier(const std::vector<sf::Vector2f> &points)
        : m_points(points)
    {
    }

    Bezier::~Bezier() = default;

    XmlValue toXml(const Bezier &bezier)
    {
        XmlValue xml("Bezier", {});
        auto &content = xml.asContent();
        for (auto &point : bezier.asPoints())
        {
            XmlValue point_xml{"Point", {}};
            point_xml["position"] = toString(point);
            content.push_back(std::move(point_xml));
        }
        return std::move(xml);
    }

    void fromXml(Bezier &bezier, const XmlValue &xml)
    {
        bezier = {};
        if (xml.isTag())
        {
            auto &points = bezier.asPoints();
            for (auto &point_xml : xml.asContent())
            {
                sf::Vector2f point{};
                fromString(point, point_xml.getAttribute("position", "0,0"));
                points.push_back(point);
            }
        }
    }

    namespace bezier
    {

        XmlValue XmlConverter::toXml(const Line *const value) const
        {
            const Bezier *bezier = nullptr;
            if (value && typeid(*value) == typeid(Bezier) && (bezier = dynamic_cast<const Bezier *>(value)))
            {
                auto xml = cacto::toXml(*bezier);
                return std::move(xml);
            }
            return nullptr;
        }

        Line *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.isTag() && xml.getName() == "Bezier")
            {
                auto bezier = std::make_shared<Bezier>();
                cacto::fromXml(*bezier, xml);
                Line::XmlStack.push(bezier);
                return bezier.get();
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}