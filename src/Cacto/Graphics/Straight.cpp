#include <Cacto/Graphics/Straight.hpp>

namespace cacto
{

    szt Straight::getPointCount() const
    {
        return 2;
    }

    sf::Vector2f Straight::getPoint(szt index, szt precision) const
    {
        if (precision < 1)
            precision = 1;
        index %= 2 * precision;
        auto step = (m_end - m_begin) / f32t(precision);
        auto point = m_begin + step * f32t(index);
        return point;
    }

    JsonValue Straight::toJson() const
    {
        auto json = JsonValue::ObjectValue;
        json["type"] = "Straight";
        json["begin"] = {f64t(m_begin.x), f64t(m_begin.y)};
        json["end"] = {f64t(m_end.x), f64t(m_end.y)};
        return json;
    }

    void Straight::fromJson(const JsonValue &json)
    {
        auto &begin = json["begin"];
        auto &end = json["end"];
        m_begin = {f32t(begin[0].asNumber()), f32t(begin[1].asNumber())};
        m_end = {f32t(end[0].asNumber()), f32t(end[1].asNumber())};
    }

    Straight::Straight(const sf::Vector2f &begin, const sf::Vector2f &end)
        : m_begin(begin), m_end(end)
    {
    }

    Straight::~Straight() = default;

}