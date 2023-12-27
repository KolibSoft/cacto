#pragma once

#include <Cacto/Config.hpp>

namespace sf
{
    class Event;
}

namespace cacto
{

    class Focusable
    {

    public:
        virtual void focus() = 0;
        virtual void unfocus() = 0;

        Focusable() = default;
        virtual ~Focusable() = default;
    };

}
