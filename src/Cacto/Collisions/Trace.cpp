#include <stdexcept>
#include <Cacto/Graphics/Geometry.hpp>
#include <Cacto/Graphics/Utils.hpp>
#include <Cacto/Collisions/Trace.hpp>

namespace cacto
{

    const SharedGeometry &Trace::getGeometry() const
    {
        return m_geometry;
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

    szt Trace::getPointCount() const
    {
        auto pCount = m_geometry->getPointCount() * m_precision;
        return pCount;
    }

    const sf::Vector2f &Trace::getPoint(szt index) const
    {
        if (!m_geometry)
            throw std::runtime_error("This trace do not has a geometry");
        if (m_points.size() <= index)
        {
            auto point = m_transform.transformPoint(m_geometry->getPoint(index, m_precision));
            m_points.push_back(point);
        }
        return m_points[index];
    }

    bool Trace::checkCollision(const Trace &other) const
    {
        auto result = zoneWith(m_bounds, other.m_bounds) && checkCollisionPart(other) || other.checkCollisionPart(*this);
        return result;
    }

    Trace::Trace(const SharedGeometry &geometry, const sf::Transform &transform, szt precision)
        : m_geometry(geometry),
          m_transform(transform),
          m_precision(precision),
          m_iTransform(transform.getInverse()),
          m_bounds(),
          m_points()
    {
        if (m_geometry)
            m_bounds = m_transform.transformRect(m_geometry->getBounds());
    }

    Trace::~Trace() = default;

    bool Trace::checkCollisionPart(const Trace &other) const
    {
        if (!m_geometry || !other.m_geometry)
            throw std::runtime_error("One fo the traces do not have a geometry");
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