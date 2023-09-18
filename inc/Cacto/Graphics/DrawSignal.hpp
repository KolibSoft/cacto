#ifndef CACTO_DRAW_SIGNAL_HPP
#define CACTO_DRAW_SIGNAL_HPP

#include <Cacto/Core/Signal.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{

    class RenderTarget;
    class RenderStates;

}

namespace cacto
{

    class CACTO_GRAPHICS_API DrawSignal
        : public virtual Signal
    {
    public:
        sf::RenderTarget &target;
        const sf::RenderStates &states;

        DrawSignal(sf::RenderTarget &_target, const sf::RenderStates &_states);
        virtual ~DrawSignal();
    };

}

#endif