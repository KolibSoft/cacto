#ifndef CACTO_COLORING_HPP
#define CACTO_COLORING_HPP

#include <SFML/Graphics/Color.hpp>
#include <Cacto/Animations/Animation.hpp>

namespace cacto
{

    class CACTO_ANIMATIONS_API Coloring
        : public Animation
    {

    public:
        const sf::Color &getFrom() const;
        void setFrom(const sf::Color &value);

        const sf::Color &getTo() const;
        void setTo(const sf::Color &value);

        sf::Color getValue(const sf::Time &lifetime) const;

        Coloring();
        virtual ~Coloring();

    private:
        sf::Color m_from;
        sf::Color m_to;
    };

}

#endif