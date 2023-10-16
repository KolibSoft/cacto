#ifndef CACTO_ANIMATION_HPP
#define CACTO_ANIMATION_HPP

#include <SFML/System/Time.hpp>
#include <Cacto/Animations/Export.hpp>

namespace cacto
{

    class CACTO_ANIMATIONS_API Animation
    {

    public:
        const sf::Time &getDelay() const;
        void setDelay(const sf::Time &value);

        const sf::Time &getDuration() const;
        void setDuration(const sf::Time &value);

        f32t getRatio(const sf::Time &lifetime) const;
        szt getIndex(const sf::Time &lifetime, szt frameCount) const;

        Animation();
        virtual ~Animation();

    private:
        sf::Time m_delay;
        sf::Time m_duration;
    };

}

#endif