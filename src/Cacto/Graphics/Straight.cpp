#include <SFML/System/Vector2.hpp>
#include <Cacto/Core/VectorUtils.hpp>
#include <Cacto/Graphics/VectorUtils.hpp>
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

    XmlValue toXml(const Straight &straight)
    {
        XmlValue xml("Straight", {});
        auto begin = toString(straight.getBegin());
        auto end = toString(straight.getEnd());
        xml["begin"] = begin;
        xml["end"] = end;
        return std::move(xml);
    }

    Straight toStraight(const XmlValue &xml)
    {
        Straight straight{};
        auto begin = xml.getAttribute("begin", "0,0");
        auto end = xml.getAttribute("end", "0,0");
        straight.setBegin(toVector(begin));
        straight.setEnd(toVector(end));
        return std::move(straight);
    }

    namespace straight
    {

        XmlValue XmlConverter::toXml(const Line *const value) const
        {
            const Straight *straight = nullptr;
            if (value && typeid(*value) == typeid(Straight) && (straight = dynamic_cast<const Straight *>(value)))
            {
                auto xml = cacto::toXml(*straight);
                return std::move(xml);
            }
            return nullptr;
        }

        Line *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.isTag() && xml.getName() == "Straight")
            {
                auto straight = new Straight();
                *straight = toStraight(xml);
                return straight;
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}