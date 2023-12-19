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

}