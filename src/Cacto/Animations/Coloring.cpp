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

    XmlValue toXml(const Coloring &coloring)
    {
        auto xml = toXml((const Animation &)coloring);
        xml.setName("Coloring");
        xml["from"] = toString(coloring.getFrom());
        xml["to"] = toString(coloring.getTo());
        return std::move(xml);
    }

    void fromXml(Coloring &coloring, const XmlValue &xml)
    {
        fromXml((Animation &)coloring, xml);
        sf::Color from{};
        sf::Color to{};
        fromString(from, xml.getAttribute("from", "#FFFFFFFF"));
        fromString(to, xml.getAttribute("to", "#FFFFFFFF"));
        coloring.setFrom(from);
        coloring.setTo(to);
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
            if (xml.isTag() && xml.getName() == "Linear")
            {
                auto coloring = std::make_shared<Coloring>();
                cacto::fromXml(*coloring, xml);
                Animation::XmlStack.push(coloring);
                return coloring.get();
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}
