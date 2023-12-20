#pragma once

#include <Cacto/Window/Export.hpp>

namespace sf
{
    class Event;
}

namespace cacto
{

    class CACTO_WINDOW_API Focusable
    {

    public:
        void focus();
        void unfocus();

        Focusable() = default;
        virtual ~Focusable() = default;

    protected:
        virtual void onFocus(const sf::Event &event) = 0;
        virtual void onUnfocus(const sf::Event &event) = 0;
    };

}
