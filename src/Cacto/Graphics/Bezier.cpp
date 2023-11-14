#include <math.h>
#include <Cacto/Graphics/Bezier.hpp>

namespace cacto
{

    i32t binomialCoefficient(i32t n, i32t k)
    {
        if (k == 0 || k == n)
            return 1;
        auto coefficient = binomialCoefficient(n - 1, k - 1) + binomialCoefficient(n - 1, k);
        return coefficient;
    }

    szt Bezier::getPointCount() const
    {
        return m_points.size();
    }

    sf::Vector2f Bezier::getPoint(szt index, szt precision) const
    {
        if (precision < 1)
            precision = 1;
        index %= m_points.size() * precision;
        auto t = f32t(index) / f32t(m_points.size() * precision - 1);
        auto n = m_points.size() - 1;
        sf::Vector2f point{0, 0};
        for (int i = 0; i <= n; ++i)
        {
            f32t coeff = binomialCoefficient(n, i) * pow(1 - t, n - i) * pow(t, i);
            point += coeff * m_points[i];
        }
        return point;
    }

    Bezier::Bezier(const std::vector<sf::Vector2f> &points)
        : m_points(points)
    {
    }

    Bezier::~Bezier() = default;

}