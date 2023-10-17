#ifndef CACTO_DIMENSION_HPP
#define CACTO_DIMENSION_HPP

#include <memory>
#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <Cacto/Collisions/Export.hpp>

namespace cacto
{

    class Trace;
    class Body;
    class Dimension;
    using SharedDimension = std::shared_ptr<Dimension>;

    class CACTO_COLLISIONS_API Dimension
        : public virtual sf::Drawable
    {

    public:
        const sf::FloatRect &getZone() const;
        szt getCapacity() const;

        bool hasZone(const sf::FloatRect &zone) const;
        Dimension *const locate(const sf::FloatRect &zone) const;

        void append(Body &body, const Trace &trace);

        void collisions(Body &body, const Trace &trace);
        void collisionsChildren(Body &body, const Trace &trace);

        Dimension &locateCollisions(Body &body, const Trace &trace);

        bool isEmpty() const;
        void clean();

        Dimension(const sf::FloatRect &zone, szt capacity = 16);
        virtual ~Dimension();

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

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
        SharedDimension m_topLeft;
        SharedDimension m_topRight;
        SharedDimension m_bottomLeft;
        SharedDimension m_bottomRight;

        static Dimension &locateCollisions(Dimension &dimension, const Holder &holder);

        struct Holder
        {
        public:
            Holder(Body *const _body, const Trace *const _trace) : body(_body), trace(_trace) {}
            virtual ~Holder() = default;

            Body *body;
            const Trace *trace;
        };
    };

}

#endif