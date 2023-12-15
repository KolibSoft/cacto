#include <Cacto/Animations/Linear.hpp>

namespace cacto
{

    const f32t &Linear::getFrom() const
    {
        return m_from;
    }

    void Linear::setFrom(const f32t &value)
    {
        m_from = value;
    }

    const f32t &Linear::getTo() const
    {
        return m_to;
    }

    void Linear::setTo(const f32t &value)
    {
        m_to = value;
    }

    f32t Linear::getValue(const sf::Time &lifetime) const
    {
        auto ratio = getRatio(lifetime);
        auto step = m_to - m_from;
        auto value = m_from + step * ratio;
        return value;
    }

    Linear::Linear(f32t from, f32t to, const sf::Time &delay, const sf::Time &duration, Direction direction, Mode mode)
        : Animation(delay, duration, direction, mode),
          m_from(from),
          m_to(to)
    {
    }

    Linear::~Linear() = default;

    JsonValue toJson(const Linear &linear)
    {
        auto json = toJson((const Animation &)linear);
        json["from"] = linear.getFrom();
        json["to"] = linear.getTo();
        return std::move(json);
    }

    void fromJson(Linear &linear, const JsonValue &json)
    {
        fromJson((Animation &)linear, json);
        linear.setFrom(f32t(json["from"].getNumber()));
        linear.setTo(f32t(json["to"].getNumber()));
    }

    namespace linear
    {

        JsonValue JsonConverter::toJson(const Animation *const value) const
        {
            const Linear *linear = nullptr;
            if (value && typeid(*value) == typeid(Linear) && (linear = dynamic_cast<const Linear *>(value)))
            {
                auto json = cacto::toJson(*linear);
                json["$type"] = "Linear";
                return std::move(json);
            }
            return nullptr;
        }

        Animation *JsonConverter::fromJson(const JsonValue &json) const
        {
            if (json.isObject() && json["$type"] == "Linear")
            {
                auto linear = new Linear();
                cacto::fromJson(*linear, json);
                return linear;
            }
            return nullptr;
        }

        JsonConverter Converter{};

    }

}
