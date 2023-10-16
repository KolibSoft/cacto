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

    f32t Animation::getRatio(const sf::Time &lifetime) const
    {
        if (m_duration == sf::Time::Zero)
            return 1.0;
        if (lifetime < m_delay)
            return 0.0;
        auto _lifetime = lifetime - m_delay;
        if (_lifetime > m_duration)
            return 1.0;
        auto ratio = _lifetime / m_duration;
        return ratio;
    }

    szt Animation::getIndex(const sf::Time &lifetime, szt frameCount) const
    {
        auto ratio = getRatio(lifetime);
        auto index = szt(frameCount * ratio) - 1;
        return index;
    }

    Animation::Animation()
        : m_delay(), m_duration()
    {
    }

    Animation::~Animation() = default;

}