#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Animations/Coloring.hpp>

namespace cacto
{

    inline const sf::Color &Coloring::getFrom() const
    {
        return m_from;
    }

    inline void Coloring::setFrom(const sf::Color &value)
    {
        m_from = value;
    }

    inline const sf::Color &Coloring::getTo() const
    {
        return m_to;
    }

    inline void Coloring::setTo(const sf::Color &value)
    {
        m_to = value;
    }

    inline sf::Color Coloring::getValue(const sf::Time &lifetime) const
    {
        auto t = getRatio(lifetime);
        auto t2 = t * t;
        auto t3 = t2 * t;
        auto fromBlend = 2 * t3 - 3 * t2 + 1;
        auto toBlend = -2 * t3 + 3 * t2;
        auto step = m_to - m_from;
        sf::Color value{u8t(m_from.r * fromBlend + m_to.r * toBlend),
                        u8t(m_from.g * fromBlend + m_to.g * toBlend),
                        u8t(m_from.b * fromBlend + m_to.b * toBlend),
                        u8t(m_from.a * fromBlend + m_to.a * toBlend)};
        return value;
    }

    inline Coloring::Coloring(const sf::Color &from, const sf::Color &to, const sf::Time &delay, const sf::Time &duration, Direction direction, Mode mode)
        : Animation(delay, duration, direction, mode),
          m_from(from),
          m_to(to)
    {
    }

    inline Coloring::~Coloring() = default;

    JsonValue toJson(const Coloring &coloring)
    {
        auto json = toJson((const Animation &)coloring);
        json["from"] = toString(coloring.getFrom());
        json["to"] = toString(coloring.getTo());
        return std::move(json);
    }

    void fromJson(Coloring &coloring, const JsonValue &json)
    {
        fromJson((Animation &)coloring, json);
        sf::Color from{};
        cacto::fromString(from, json["from"].getString("#FFFFFFFF"));
        coloring.setFrom(from);
        sf::Color to{};
        cacto::fromString(to, json["to"].getString("#FFFFFFFF"));
        coloring.setTo(to);
    }

    namespace coloring
    {

        JsonValue JsonConverter::toJson(const Animation *const value) const
        {
            const Coloring *coloring = nullptr;
            if (value && (coloring = dynamic_cast<const Coloring *>(value)))
            {
                auto json = cacto::toJson(*coloring);
                json["$type"] = "Coloring";
                return std::move(json);
            }
            return nullptr;
        }

        Animation *JsonConverter::fromJson(const JsonValue &json) const
        {
            if (json.isObject() && json["$type"] == "Coloring")
            {
                auto coloring = new Coloring();
                cacto::fromJson(*coloring, json);
                return coloring;
            }
            return nullptr;
        }

        JsonConverter Converter{};

    }

}
