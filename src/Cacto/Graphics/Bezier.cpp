#include <math.h>
#include <SFML/System/Vector2.hpp>
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

    const sf::Vector2f &Bezier::getControlPoint(szt index) const
    {
        return m_points[index];
    }

    void Bezier::setControlPoint(szt index, const sf::Vector2f &value)
    {
        m_points[index] = value;
    }

    void Bezier::clear()
    {
        m_points.clear();
    }

    void Bezier::append(const sf::Vector2f &point)
    {
        m_points.push_back(point);
    }

    void Bezier::resize(szt count)
    {
        m_points.resize(count);
    }

    Bezier::Bezier(const std::vector<sf::Vector2f> &points)
        : m_points(points)
    {
    }

    Bezier::~Bezier() = default;

    namespace bezier
    {

        JsonValue JsonConverter::toJson(const Line *const value) const
        {
            const Bezier *bezier = nullptr;
            if (value && (bezier = dynamic_cast<const Bezier *>(value)))
            {
                auto json = JsonValue::ObjectValue;
                json["$type"] = "Bezier";
                auto &points = (json["points"] = JsonValue::ArrayValue).asArray();
                for (szt i = 0; i < bezier->getPointCount(); i++)
                {
                    auto &point = bezier->getControlPoint(i);
                    points.push_back({point.x, point.y});
                }
                return std::move(json);
            }
            return nullptr;
        }

        Line *JsonConverter::fromJson(const JsonValue &json) const
        {
            if (json.isObject() && json["$type"] == "Bezier")
            {
                auto bezier = new Bezier();
                auto &points = json["points"];
                if (points.isArray())
                    for (auto &point : points.asArray())
                        bezier->append({f32t(point[0].getNumber()), f32t(point[1].getNumber())});
                return bezier;
            }
            return nullptr;
        }

        JsonConverter Converter{};

    }

}