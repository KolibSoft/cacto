#ifndef CACTO_DIMENSION_HPP
#define CACTO_DIMENSION_HPP

#include <memory>
#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <Cacto/Physics/Export.hpp>

namespace cacto
{

    class Trace;
    class Collisionable;
    class Dimension;

    class CACTO_PHYSICS_API Dimension
    {

    public:
        const sf::FloatRect &getZone() const;
        szt getCapacity() const;

        bool hasZone(const sf::FloatRect &zone) const;
        Dimension *const locate(const sf::FloatRect &zone) const;

        void append(Collisionable &body, const Trace &trace);

        void collisions(Collisionable &body, const Trace &trace);
        void collisionsChildren(Collisionable &body, const Trace &trace);

        Dimension &locateCollisions(Collisionable &body, const Trace &trace);

        bool isEmpty() const;
        void clean();

        Dimension(const sf::FloatRect &zone, szt capacity = 16);
        virtual ~Dimension();

        Dimension(const Dimension &other);
        Dimension &operator=(const Dimension &other);

    private:
        struct Holder;

        void append(const Holder &holder);
        void split();

        void collisions(const Holder &holder);
        void collisionsChildren(const Holder &holder);

        sf::FloatRect m_zone;
        szt m_capacity;
        std::vector<Holder> m_holders;

        bool m_subdimensions;
        Dimension *m_topLeft;
        Dimension *m_topRight;
        Dimension *m_bottomLeft;
        Dimension *m_bottomRight;

        static Dimension &locateCollisions(Dimension &dimension, const Holder &holder);

        struct Holder
        {
            Collisionable *body;
            const Trace *trace;
        };
    };

}

#endif