#include <SFML/Graphics/RenderTarget.hpp>
#include <Cacto/Graphics/Rectangle.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Physics/Trace.hpp>

namespace cacto
{

    const Geometry &Trace::getGeometry() const
    {
        return *m_geometry;
    }

    szt Trace::getPrecision() const
    {
        return m_precision;
    }

    const sf::Transform &Trace::getTransform() const
    {
        return m_transform;
    }

    const sf::FloatRect &Trace::getBounds() const
    {
        return m_bounds;
    }

    const sf::Vector2f &Trace::getPoint(szt index) const
    {
        if (m_points.size() <= index)
        {
            auto point = m_transform.transformPoint(m_geometry->getPoint(index, m_precision));
            m_points.push_back(point);
        }
        return m_points[index];
    }

    szt Trace::getPointCount() const
    {
        auto pCount = m_geometry->getPointCount() * m_precision;
        return pCount;
    }

    bool Trace::checkCollision(const Trace &other) const
    {
        auto result = zoneWith(m_bounds, other.m_bounds) && (checkCollisionPart(other) || other.checkCollisionPart(*this));
        return result;
    }

    Trace::Trace(const Geometry &geometry, const sf::Transform &transform, szt precision)
        : m_geometry(&geometry),
          m_transform(transform),
          m_precision(precision),
          m_iTransform(transform.getInverse()),
          m_bounds(),
          m_points(),
          m_invalid(true),
          m_geometryArray(),
          m_boundsArray()
    {
        m_bounds = m_transform.transformRect(m_geometry->getBounds());
    }

    Trace::~Trace() = default;

    void Trace::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (m_invalid)
        {
            m_boundsArray.setPrimitiveType(sf::PrimitiveType::LineStrip);
            setPoints(m_boundsArray, Rectangle({m_bounds.left, m_bounds.top}, {m_bounds.width, m_bounds.height}));
            m_boundsArray.append(m_boundsArray[0]);
            setColor(m_boundsArray, sf::Color::Blue);

            m_geometryArray.setPrimitiveType(sf::PrimitiveType::LineStrip);
            setPoints(m_geometryArray, *m_geometry);
            m_geometryArray.append(m_geometryArray[0]);
            setColor(m_geometryArray, sf::Color::Red);

            m_invalid = false;
        }

        target.draw(m_boundsArray, states);

        auto _states = states;
        _states.transform *= m_transform;
        target.draw(m_geometryArray, _states);
    }

    bool Trace::checkCollisionPart(const Trace &other) const
    {
        auto pointCount = other.getPointCount();
        for (szt i = 0; i < pointCount; i++)
        {
            auto point = m_iTransform.transformPoint(other.getPoint(i));
            if (m_geometry->containsPoint(point))
                return true;
        }
        return false;
    }

}