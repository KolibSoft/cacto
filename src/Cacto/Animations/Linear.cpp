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

    XmlValue toXml(const Linear &linear)
    {
        auto xml = toXml((const Animation &)linear);
        xml.setName("Linear");
        xml["from"] = std::to_string(linear.getFrom());
        xml["to"] = std::to_string(linear.getTo());
        return std::move(xml);
    }

    void fromXml(Linear &linear, const XmlValue &xml)
    {
        fromXml((Animation &)linear, xml);
        linear.setFrom(std::stof(xml.getAttribute("from", "0")));
        linear.setTo(std::stof(xml.getAttribute("to", "0")));
    }

    namespace linear
    {

        XmlValue XmlConverter::toXml(const Animation *const value) const
        {
            const Linear *linear = nullptr;
            if (value && typeid(*value) == typeid(Linear) && (linear = dynamic_cast<const Linear *>(value)))
            {
                auto xml = cacto::toXml(*linear);
                return std::move(xml);
            }
            return nullptr;
        }

        Animation *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.isTag() && xml.getName() == "Linear")
            {
                auto linear = std::make_shared<Linear>();
                cacto::fromXml(*linear, xml);
                Animation::XmlStack.push(linear);
                return linear.get();
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

}
