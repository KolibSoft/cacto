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
        auto tranform = other.getTransform() * getInverseTransform();
        auto geometry = other.getGeometry();
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