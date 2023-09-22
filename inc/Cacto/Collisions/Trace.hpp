#ifndef CACTO_TRACE_HPP
#define CACTO_TRACE_HPP

#include <memory>
#include <vector>
#include <SFML/Graphics/Transform.hpp>
#include <Cacto/Collisions/Export.hpp>

namespace cacto
{

    class Geometry;
    using SharedGeometry = std::shared_ptr<Geometry>;

    class Body;

    class CACTO_COLLISIONS_API Trace
    {

    public:
        Body &getBody() const;
        const SharedGeometry &getGeometry() const;
        szt getPrecision() const;
        const sf::Transform &getTransform() const;
        const sf::FloatRect &getBounds() const;

        szt getPointCount() const;
        const sf::Vector2f &getPoint(szt index) const;

        bool checkCollision(const Trace &other) const;

        Trace(Body &body, const sf::Transform &transform, const SharedGeometry &geometry, szt precision = 1);
        virtual ~Trace();

    private:
        bool checkCollisionPart(const Trace &other) const;

        Body *m_body;
        sf::Transform m_transform;
        sf::Transform m_iTransform;
        SharedGeometry m_geometry;
        szt m_precision;
        sf::FloatRect m_bounds;

        mutable std::vector<sf::Vector2f> m_points;
    };

}

#endif