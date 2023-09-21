#include <Cacto/Graphics/Geometry.hpp>
#include <Cacto/Collisions/Body.hpp>

namespace cacto
{

    const SharedGeometry &Body::getGeometry() const
    {
        return m_geometry;
    }

    void Body::setGeometry(const SharedGeometry &value)
    {
        m_geometry = value;
    }

    sf::FloatRect Body::getBounds() const
    {
        auto bounds = getTransform().transformRect(m_geometry->getBounds());
        return bounds;
    }

    bool Body::checkCollision(const Body &other) const
    {
        auto collision = checkCollisionPart(other) || other.checkCollisionPart(*this);
        return collision;
    }

    Body::Body()
        : m_geometry(nullptr)
    {
    }

    Body::~Body() = default;

    bool Body::checkCollisionPart(const Body &other) const
    {
        auto tranform = getInverseTransform() * other.getTransform();
        auto geometry = other.m_geometry;
        auto pointCount = geometry->getPointCount();
        for (szt i = 0; i < pointCount; i++)
        {
            auto point = tranform.transformPoint(geometry->getPoint(i));
            if (m_geometry->containsPoint(point))
                return true;
        }
        return false;
    }

}