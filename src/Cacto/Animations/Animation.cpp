#include <Cacto/Animations/Animation.hpp>

namespace cacto
{

    const sf::Time &Animation::getDelay() const
    {
        return m_delay;
    }

    void Animation::setDelay(const sf::Time &value)
    {
        m_delay = value;
    }

    const sf::Time &Animation::getDuration() const
    {
        return m_duration;
    }

    void Animation::setDuration(const sf::Time &value)
    {
        m_duration = value;
    }

    Animation::Direction Animation::getDirection() const
    {
        return m_direction;
    }

    void Animation::setDirection(Direction value)
    {
        m_direction = value;
    }

    Animation::Mode Animation::getMode() const
    {
        return m_mode;
    }

    void Animation::setMode(Mode value)
    {
        m_mode = value;
    }

    f32t Animation::getRatio(const sf::Time &lifetime) const
    {
        auto _lifetime = lifetime;
        switch (m_direction)
        {
        case Forward:
        {
        forward:
            if (m_duration == sf::Time::Zero)
                return 1.0;
            if (_lifetime < m_delay)
                return 0.0;
            _lifetime -= m_delay;
            if (_lifetime > m_duration)
                switch (m_mode)
                {
                case Once:
                    return 1.0;
                    break;
                case Repeat:
                    _lifetime -= m_duration;
                    goto forward;
                    break;
                case Flip:
                    _lifetime -= m_duration;
                    goto reverse;
                    break;
                }
            auto ratio = _lifetime / m_duration;
            return ratio;
        }
        break;
        case Reverse:
        {
        reverse:
            if (m_duration == sf::Time::Zero)
                return 0.0;
            if (lifetime < m_delay)
                return 1.0;
            _lifetime -= m_delay;
            if (_lifetime > m_duration)
                switch (m_mode)
                {
                case Once:
                    return 0.0;
                    break;
                case Repeat:
                    _lifetime -= m_duration;
                    goto reverse;
                    break;
                case Flip:
                    _lifetime -= m_duration;
                    goto forward;
                    break;
                }
            auto ratio = 1 - _lifetime / m_duration;
            return ratio;
        }
        break;
        }
        throw std::runtime_error("Invalid Animation state");
    }

    szt Animation::getIndex(const sf::Time &lifetime, szt frameCount) const
    {
        auto ratio = getRatio(lifetime);
        auto index = szt(frameCount * ratio) - 1;
        return index;
    }

    Animation::Animation(const sf::Time &delay, const sf::Time &duration, Direction direction, Mode mode)
        : m_delay(delay),
          m_duration(duration),
          m_direction(direction),
          m_mode(mode)
    {
    }

    Animation::~Animation() = default;

    std::string toString(const Animation::Direction &direction)
    {
        if (direction == Animation::Forward)
            return "Forward";
        else if (direction == Animation::Reverse)
            return "Reverse";
        else
            throw std::runtime_error("Not supported direction value");
    }

    void fromString(Animation::Direction &direction, const std::string &string)
    {
        if (string == "Forward")
            direction = Animation::Forward;
        else if (string == "Reverse")
            direction = Animation::Reverse;
        else
            throw std::runtime_error("Not supported direction value");
    }

    std::string toString(const Animation::Mode &mode)
    {
        if (mode == Animation::Once)
            return "Once";
        else if (mode == Animation::Repeat)
            return "Repeat";
        else if (mode == Animation::Flip)
            return "Flip";
        else
            throw std::runtime_error("Not supported mode value");
    }

    void fromString(Animation::Mode &mode, const std::string &string)
    {
        if (string == "Once")
            mode = Animation::Once;
        else if (string == "Repeat")
            mode = Animation::Repeat;
        else if (string == "Flip")
            mode = Animation::Flip;
        else
            throw std::runtime_error("Not supported mode value");
    }

    XmlValue toXml(const Animation &animation)
    {
        XmlValue xml{"Animation", {}};
        xml["delay"] = animation.getDelay().asSeconds();
        xml["duration"] = animation.getDuration().asSeconds();
        xml["direction"] = toString(animation.getDirection());
        xml["mode"] = toString(animation.getMode());
        return std::move(xml);
    }

    void fromXml(Animation &animation, const XmlValue &xml)
    {
        animation.setDelay(sf::seconds(std::stof(xml.getAttribute("delay", "0"))));
        animation.setDuration(sf::seconds(std::stof(xml.getAttribute("duration", "0"))));
        Animation::Direction direction{};
        fromString(direction, xml.getAttribute("direction", "Forward"));
        animation.setDirection(direction);
        Animation::Mode mode{};
        fromString(mode, xml.getAttribute("mode", "Once"));
        animation.setMode(mode);
    }

    XmlValue toXml(const Animation *const &animation)
    {
        auto xml = XmlConverter<Animation>::xml(animation);
        return std::move(xml);
    }

    void fromXml(Animation *&animation, const XmlValue &xml)
    {
        auto value = XmlConverter<Animation>::value(xml);
        animation = value;
    }

    namespace animation
    {

        XmlValue XmlConverter::toXml(const Animation *const value) const
        {
            const Animation *animation = nullptr;
            if (value && typeid(*value) == typeid(Animation) && (animation = dynamic_cast<const Animation *>(value)))
            {
                auto xml = cacto::toXml(*animation);
                return std::move(xml);
            }
            return nullptr;
        }

        Animation *XmlConverter::fromXml(const XmlValue &xml) const
        {
            if (xml.isTag() && xml.getName() == "Animation")
            {
                auto animation = std::make_shared<Animation>();
                cacto::fromXml(*animation, xml);
                Animation::XmlStack.push(animation);
                return animation.get();
            }
            return nullptr;
        }

        XmlConverter Converter{};

    }

    ResourceStack<Animation> Animation::XmlStack{};

}