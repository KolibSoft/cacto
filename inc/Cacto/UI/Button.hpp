#ifndef CACTO_BUTTON_HPP
#define CACTO_BUTTON_HPP

#include <Cacto/Window/Clickable.hpp>
#include <Cacto/Window/Focusable.hpp>
#include <Cacto/UI/Label.hpp>

namespace cacto
{

    class CACTO_UI_API Button
        : public Label,
          public virtual Clickable,
          public virtual Focusable
    {

    public:
        const EventListener &getOnClickListener() const;
        Button &setOnClickListener(const EventListener &value);

        Button(const sf::Font &font, const sf::String &string = "", u32t characterSize = 30);
        Button(sf::Font &&font, const sf::String &string = "", u32t characterSize = 30) = delete;

        virtual ~Button();

        Button(const Button &other);
        Button &operator=(const Button &other);

    protected:
        bool onEvent(const sf::Event &event) override;

        void onClick(const sf::Event &event) override;
        void onFocus(const sf::Event &event) override;
        void onUnfocus(const sf::Event &event) override;

    private:
        EventListener m_onClick;
        bool m_focused;
    };

}

#endif