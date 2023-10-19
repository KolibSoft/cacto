#ifndef CACTO_INPUTABLE_HPP
#define CACTO_INPUTABLE_HPP

#include <Cacto/Window/Export.hpp>

namespace sf
{
    class Event;
}

namespace cacto
{

    class CACTO_WINDOW_API Inputable
    {

    public:
        void input(u32t unicode);

        Inputable() = default;
        virtual ~Inputable() = default;

    protected:
        virtual void onInput(const sf::Event &event) = 0;
    };

}

#endif