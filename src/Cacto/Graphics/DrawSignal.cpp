#include <Cacto/Graphics/DrawSignal.hpp>

namespace cacto
{

    DrawSignal::DrawSignal(sf::RenderTarget &_target, const sf::RenderStates &_states)
        : target(_target), states(_states)
    {
    }

    DrawSignal::~DrawSignal() = default;

}