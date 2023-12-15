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

    JsonValue toJson(const Animation &animation)
    {
        auto json = JsonValue::ObjectValue;
        json["delay"] = animation.getDelay().asSeconds();
        json["duration"] = animation.getDuration().asSeconds();
        json["direction"] = toString(animation.getDirection());
        json["mode"] = toString(animation.getMode());
        return std::move(json);
    }

    void fromJson(Animation &animation, const JsonValue &json)
    {
        animation.setDelay(sf::seconds(json["delay"].getNumber()));
        animation.setDuration(sf::seconds(json["duration"].getNumber()));
        Animation::Direction direction{};
        fromString(direction, json["direction"].getString("Forward"));
        animation.setDirection(direction);
        Animation::Mode mode{};
        fromString(mode, json["mode"].getString("Once"));
        animation.setMode(mode);
    }

    JsonValue toJson(const Animation *const &animation)
    {
        auto json = JsonConverter<Animation>::json(animation);
        return std::move(json);
    }

    void fromJson(Animation *&animation, const JsonValue &json)
    {
        auto value = JsonConverter<Animation>::value(json);
        animation = value;
    }

    namespace animation
    {

        JsonValue JsonConverter::toJson(const Animation *const value) const
        {
            const Animation *animation = nullptr;
            if (value && typeid(*value) == typeid(Animation) && (animation = dynamic_cast<const Animation *>(value)))
            {
                auto json = cacto::toJson(*animation);
                json["$type"] = "Animation";
                return std::move(json);
            }
            return nullptr;
        }

        Animation *JsonConverter::fromJson(const JsonValue &json) const
        {
            if (json.isObject() && json["$type"] == "Animation")
            {
                auto animation = new Animation();
                cacto::fromJson(*animation, json);
                return animation;
            }
            return nullptr;
        }

        JsonConverter Converter{};

    }

}