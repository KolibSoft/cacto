#include <Cacto/Window/EventSignal.hpp>

namespace cacto
{

    EventSignal::EventSignal(const sf::Event &_event)
        : event(_event)
    {
    }

    EventSignal::~EventSignal() = default;

}