#include <math.h>
#include <Cacto/Graphics/Bezier.hpp>

namespace cacto
{

    sf::Vector2f Bezier::getPoint(szt index, szt precision) const
    {
        if (precision < 1)
            precision = 1;
        index %= precision;
        auto n = m_points.size() - 1;
        auto at = float(index) / precision;
        sf::Vector2f point{0, 0};
        for (szt i = 0; i <= n; i++)
        {
            float binomial = 1.0f;
            for (int j = 0; j < i; j++)
                binomial *= float(n - j) / float(j + 1);
            float factorA = pow(1.0f - at, n - i);
            float factorB = pow(at, i);
            point += binomial * factorA * factorB * m_points[i];
        }
        return point;
    }

    sf::Vector2f Bezier::getDirection(szt index, szt precision) const
    {
        if (precision < 1)
            precision = 1;
        index %= precision;
        auto begin = getPoint(index, precision);
        auto end = getPoint(index + 1, precision);
        auto direction = (end - begin).normalized();
        return direction;
    }

    Bezier::Bezier(const std::vector<sf::Vector2f> &points)
        : m_points(points)
    {
    }

    Bezier::~Bezier() = default;

}