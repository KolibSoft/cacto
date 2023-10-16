#ifndef CACTO_ANIMATION_INL
#define CACTO_ANIMATION_INL

#include <Cacto/Animations/Animation.hpp>

namespace cacto
{

    template <typename T>
    inline const T &Animation<T>::getFrom() const
    {
        return m_from;
    }

    template <typename T>
    inline void Animation<T>::setFrom(const T &value)
    {
        m_from = value;
    }

    template <typename T>
    inline const T &Animation<T>::getTo() const
    {
        return m_to;
    }

    template <typename T>
    inline void Animation<T>::setTo(const T &value)
    {
        m_to = value;
    }

    template <typename T>
    inline const sf::Time &Animation<T>::getDelay() const
    {
        return m_delay;
    }

    template <typename T>
    inline void Animation<T>::setDelay(const sf::Time &value)
    {
        m_delay = value;
    }

    template <typename T>
    inline const sf::Time &Animation<T>::getDuration() const
    {
        return m_duration;
    }

    template <typename T>
    inline void Animation<T>::setDuration(const sf::Time &value)
    {
        m_duration = value;
    }

    template <typename T>
    inline T Animation<T>::getValue(const sf::Time &time) const
    {
        if (m_duration == sf::Time::Zero)
            return m_to;
        if (time < m_delay)
            return m_from;
        auto _time = time - m_delay;
        if (_time > m_duration)
            return m_to;
        auto step = m_to - m_from;
        auto ratio = _time / m_duration;
        auto value = m_from + step * ratio;
        return value;
    }

    template <typename T>
    inline Animation<T>::Animation() = default;

    template <typename T>
    inline Animation<T>::~Animation() = default;

    ///////////////////////////////////////////////////////////////////////////////

    inline const sf::Color &Animation<sf::Color>::getFrom() const
    {
        return m_from;
    }

    inline void Animation<sf::Color>::setFrom(const sf::Color &value)
    {
        m_from = value;
    }

    inline const sf::Color &Animation<sf::Color>::getTo() const
    {
        return m_to;
    }

    inline void Animation<sf::Color>::setTo(const sf::Color &value)
    {
        m_to = value;
    }

    inline const sf::Time &Animation<sf::Color>::getDelay() const
    {
        return m_delay;
    }

    inline void Animation<sf::Color>::setDelay(const sf::Time &value)
    {
        m_delay = value;
    }

    inline const sf::Time &Animation<sf::Color>::getDuration() const
    {
        return m_duration;
    }

    inline void Animation<sf::Color>::setDuration(const sf::Time &value)
    {
        m_duration = value;
    }

    inline sf::Color Animation<sf::Color>::getValue(const sf::Time &time) const
    {
        if (m_duration == sf::Time::Zero)
            return m_to;
        if (time < m_delay)
            return m_from;
        auto _time = time - m_delay;
        if (_time > m_duration)
            return m_to;

        auto t = _time / m_duration;
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

    inline Animation<sf::Color>::Animation() = default;

    inline Animation<sf::Color>::~Animation() = default;

}

#endif