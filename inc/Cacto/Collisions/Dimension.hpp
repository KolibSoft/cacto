#ifndef CACTO_DIMENSION_HPP
#define CACTO_DIMENSION_HPP

#include <memory>
#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <Cacto/Collisions/Export.hpp>

namespace cacto
{

    class Body;

    class CACTO_COLLISIONS_API Dimension
    {

    public:
        struct Trace;

        const std::vector<Trace> &getTraces() const;

        bool hasZone(const sf::FloatRect &zone) const;
        Dimension *const locate(const sf::FloatRect &zone) const;

        void append(const Trace &trace);
        Dimension &collisions(Body &body);

        Dimension(const sf::FloatRect &zone);
        virtual ~Dimension();

        static Dimension &collisions(Dimension &dimension, Body &body);

        struct Trace
        {
        public:
            Trace(Body *const _body, const sf::FloatRect _bounds) : body(_body), zone(_bounds) {}
            virtual ~Trace() = default;

            Body *const body;
            const sf::FloatRect zone;
        };

    private:
        void split();

        sf::FloatRect m_zone;
        std::vector<Trace> m_traces;
        bool m_subdimensions;
        std::unique_ptr<Dimension> m_topLeft;
        std::unique_ptr<Dimension> m_topRight;
        std::unique_ptr<Dimension> m_bottomLeft;
        std::unique_ptr<Dimension> m_bottomRight;
    };

}

#endif