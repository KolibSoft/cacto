#include <Cacto/Core/TimeUtils.hpp>
#include <Cacto/Graphics/ColorUtils.hpp>
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

    XmlValue toXml(const Coloring &coloring)
    {
        auto xml = toXml((const Animation &)coloring);
        xml.setName("Coloring");
        xml["from"] = getExpression(coloring.getFrom());
        xml["to"] = getExpression(coloring.getTo());
        return std::move(xml);
    }

    Coloring toColoring(const XmlValue &xml)
    {
        Coloring coloring{};
        coloring.setDelay(toTime(xml.getAttribute("delay", "0s")));
        coloring.setDuration(toTime(xml.getAttribute("duration", "0s")));
        coloring.setDirection(toAnimationDirection(xml.getAttribute("direction", "Forward")));
        coloring.setMode(toAnimationMode(xml.getAttribute("mode", "Once")));
        coloring.setFrom(getColor(xml.getAttribute("from", "#FFFFFFFF")));
        coloring.setTo(getColor(xml.getAttribute("to", "#FFFFFFFF")));
        return std::move(coloring);
    }

    namespace coloring
    {

        XmlValue XmlConverter::toXml(const Animation *const value) const
        {
            const Coloring *coloring = nullptr;
            if (value && typeid(*value) == typeid(Coloring) && (coloring = dynamic_cast<const Coloring *>(value)))
            {
                auto xml = cacto::toXml(*coloring);
                return std::move(xml);
            }
            return nullptr;
        }

        Animation *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.isTag() && xml.getName() == "Coloring")
            {
                auto coloring = new Coloring();
                *coloring = toColoring(xml);
                return coloring;
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}
