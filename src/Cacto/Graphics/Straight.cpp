#include <Cacto/Graphics/Straight.hpp>

namespace cacto
{

    sf::Vector2f Straight::getPoint(szt index, szt precision) const
    {
        if (precision < 1)
            precision = 1;
        index %= precision;
        auto step = (m_end - m_begin) / f32t(precision);
        auto point = m_begin + step * f32t(index);
        return point;
    }

    sf::Vector2f Straight::getDirection(szt index, szt precision) const
    {
        if (precision < 1)
            precision = 1;
        index %= precision;
        auto begin = getPoint(index, precision);
        auto end = getPoint(index + 1, precision);
        auto direction = (end - begin).normalized();
        return direction;
    }

    Straight::Straight(const sf::Vector2f &begin, const sf::Vector2f &end)
        : m_begin(begin), m_end(end)
    {
    }

    Straight::~Straight() = default;

}