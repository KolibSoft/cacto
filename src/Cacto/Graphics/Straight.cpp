#include <Cacto/Lang/JsonValue.hpp>
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

    const sf::Vector2f &Straight::getBegin() const
    {
        return m_begin;
    }

    void Straight::setBegin(const sf::Vector2f &value)
    {
        m_begin = value;
    }

    const sf::Vector2f &Straight::getEnd() const
    {
        return m_end;
    }

    void Straight::setEnd(const sf::Vector2f &value)
    {
        m_end = value;
    }

    Straight::Straight(const sf::Vector2f &begin, const sf::Vector2f &end)
        : m_begin(begin), m_end(end)
    {
    }

    Straight::~Straight() = default;

    JsonValue toJson(const Straight &straight)
    {
        auto json = JsonValue::ObjectValue;
        auto &begin = straight.getBegin();
        auto &end = straight.getEnd();
        json["begin"] = {begin.x, begin.y};
        json["end"] = {end.x, end.y};
        return json;
    }

    void fromJson(Straight &straight, const JsonValue &json)
    {
        auto &begin = json["begin"];
        auto &end = json["end"];
        straight.setBegin({f32t(begin[0].getNumber()), f32t(begin[1].getNumber())});
        straight.setEnd({f32t(end[0].getNumber()), f32t(end[1].getNumber())});
    }

    namespace straight
    {

        JsonValue JsonConverter::toJson(const Line *const value) const
        {
            const Straight *straight = nullptr;
            if (value && (straight = dynamic_cast<const Straight *>(value)))
            {
                auto json = cacto::toJson(*straight);
                json["$type"] = "Straight";
                return json;
            }
            return nullptr;
        }

        Line *JsonConverter::fromJson(const JsonValue &json) const
        {
            if (json.getKind() == JsonValue::Object && json["$type"] == "Straight")
            {
                auto straight = new Straight();
                cacto::fromJson(*straight, json);
                return straight;
            }
            return nullptr;
        }

        JsonConverter Converter{};

    }

}