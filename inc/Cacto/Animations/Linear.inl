#ifndef CACTO_LINEAR_INL
#define CACTO_LINEAR_INL

#include <Cacto/Animations/Linear.hpp>

namespace cacto
{

    template <typename T>
    inline const T &Linear<T>::getFrom() const
    {
        return m_from;
    }

    template <typename T>
    inline void Linear<T>::setFrom(const T &value)
    {
        m_from = value;
    }

    template <typename T>
    inline const T &Linear<T>::getTo() const
    {
        return m_to;
    }

    template <typename T>
    inline void Linear<T>::setTo(const T &value)
    {
        m_to = value;
    }

    template <typename T>
    inline T Linear<T>::getValue(const sf::Time &lifetime) const
    {
        auto ratio = getRatio(lifetime);
        auto step = m_to - m_from;
        auto value = m_from + step * ratio;
        return value;
    }

    template <typename T>
    inline Linear<T>::Linear() = default;

    template <typename T>
    inline Linear<T>::~Linear() = default;

}

#endif