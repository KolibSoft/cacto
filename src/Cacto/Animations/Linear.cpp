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

    Linear::Linear(f32t from, f32t to, const sf::Time &delay, const sf::Time &duration)
        : Animation(delay, duration), m_from(from), m_to(to)
    {
    }

    Linear::~Linear() = default;

}
