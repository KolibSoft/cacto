#ifndef CACTO_BODY_HPP
#define CACTO_BODY_HPP

#include <memory>
#include <SFML/Graphics/Transformable.hpp>
#include <Cacto/Collisions/Export.hpp>

namespace sf
{

    template <typename T>
    class Vector2;

    using Vector2f = Vector2<cacto::f32t>;

}

namespace cacto
{

    class Geometry;
    using SharedGeometry = std::shared_ptr<Geometry>;

    class CACTO_COLLISIONS_API Body
        : public sf::Transformable
    {

    public:
        const SharedGeometry &getGeometry() const;
        void setGeometry(const SharedGeometry &value);

        bool checkCollision(const Body &other) const;

        Body();
        virtual ~Body();

    private:
        bool checkCollisionPart(const Body &other) const;

        SharedGeometry m_geometry;
    };

}

#endif