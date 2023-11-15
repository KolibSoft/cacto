#ifndef CACTO_INPUT_HPP
#define CACTO_INPUT_HPP

#include <SFML/System/String.hpp>
#include <Cacto/Window/Inputable.hpp>
#include <Cacto/Window/Focusable.hpp>
#include <Cacto/UI/Label.hpp>

namespace cacto
{

    class CACTO_UI_API Input
        : public Label,
          public virtual Inputable,
          public virtual Focusable
    {

    public:
        const EventListener &getOnInputListener() const;
        Input &setOnInputListener(const EventListener &value);

        Input(const sf::Font &font, const sf::String &string = "", u32t characterSize = 30);
        Input(sf::Font &&font, const sf::String &string = "", u32t characterSize = 30) = delete;

        virtual ~Input();

        Input(const Input &other);
        Input &operator=(const Input &other);

    protected:
        bool onEvent(const sf::Event &event) override;

        void onInput(const sf::Event &event) override;
        void onFocus(const sf::Event &event) override;
        void onUnfocus(const sf::Event &event) override;

    private:
        EventListener m_onInput;
        bool m_focused;
    };

}

#endif