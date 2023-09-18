#include <Cacto/Core/UpdateSignal.hpp>

namespace cacto
{

    UpdateSignal::UpdateSignal(const sf::Time &_time)
        : time(_time) {}

    UpdateSignal::~UpdateSignal() = default;

}