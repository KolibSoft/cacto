#pragma once

#include <SFML/System/Time.hpp>
#include <Cacto/Animations/Export.hpp>

namespace cacto
{

    class CACTO_ANIMATIONS_API Animation
    {

    public:
        enum Direction
        {
            Forward,
            Reverse
        };

        enum Mode
        {
            Once,
            Repeat,
            Flip
        };

        const sf::Time &getDelay() const;
        void setDelay(const sf::Time &value);

        const sf::Time &getDuration() const;
        void setDuration(const sf::Time &value);

        Direction getDirection() const;
        void setDirection(Direction value);

        Mode getMode() const;
        void setMode(Mode value);

        f32t getRatio(const sf::Time &lifetime) const;
        szt getIndex(const sf::Time &lifetime, szt frameCount) const;

        Animation(const sf::Time &delay = sf::Time::Zero, const sf::Time &duration = sf::Time::Zero, Direction direction = Forward, Mode mode = Once);
        virtual ~Animation();

    private:
        sf::Time m_delay;
        sf::Time m_duration;
        mutable Direction m_direction;
        Mode m_mode;
    };

}
