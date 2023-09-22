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
        struct Holder;

        const std::vector<Holder> &getHolders() const;

        bool hasZone(const sf::FloatRect &zone) const;
        Dimension *const locate(const sf::FloatRect &zone) const;

        void append(const Holder &holder);
        void append(Body &body, const Trace &trace);

        void collisions(const Holder &holder, bool subdimensions);
        void collisions(Body &body, const Trace &trace);

        Dimension(const sf::FloatRect &zone);
        virtual ~Dimension();

        static Dimension &collisions(Dimension &dimension, const Holder &holder);

        struct Holder
        {
        public:
            Holder(Body *const _body, const Trace *const _trace) : body(_body), trace(_trace) {}
            virtual ~Holder() = default;

            Body *const body;
            Trace *const trace;
        };

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        void split();

        sf::FloatRect m_zone;
        std::vector<Holder> m_holders;
        bool m_subdimensions;
        SharedDimension m_topLeft;
        SharedDimension m_topRight;
        SharedDimension m_bottomLeft;
        SharedDimension m_bottomRight;
    };

}

#endif