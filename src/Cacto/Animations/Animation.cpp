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

}