#ifndef CACTO_EVENT_SIGNAL_HPP
#define CACTO_EVENT_SIGNAL_HPP

#include <Cacto/Core/Signal.hpp>
#include <Cacto/Window/Export.hpp>

namespace sf
{
    class Event;
}

namespace cacto
{

    class CACTO_WINDOW_API EventSignal
        : public virtual Signal
    {

    public:
        const sf::Event &event;

        EventSignal(const sf::Event &_event);
        virtual ~EventSignal();
    };

}

#endif