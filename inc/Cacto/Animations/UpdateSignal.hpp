#ifndef CACTO_UPDATE_SIGNAL_HPP
#define CACTO_UPDATE_SIGNAL_HPP

#include <Cacto/Core/Signal.hpp>
#include <Cacto/Animations/Export.hpp>

namespace sf
{
    class Time;
}

namespace cacto
{

    class CACTO_ANIMATIONS_API UpdateSignal
        : public virtual Signal
    {

    public:
        const sf::Time &time;

        UpdateSignal(const sf::Time &_time);
        virtual ~UpdateSignal();
    };

}

#endif