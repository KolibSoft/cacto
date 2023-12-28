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

        bool event(const sf::Event &event) override;

        void click(sf::Mouse::Button button = sf::Mouse::Left, const sf::Vector2f &position = {0, 0}) override;
        void focus() override;
        void unfocus() override;

        Button();
        virtual ~Button();

        Button(const Button &other);
        Button &operator=(const Button &other);

    protected:
        virtual void onClick(const sf::Event &event);

    private:
        EventListener m_onClick;
        bool m_focused;
    };

    XmlValue CACTO_UI_API toXml(const Button &button);
    void CACTO_UI_API fromXml(Button &button, const XmlValue &xml);

    namespace button
    {

        class CACTO_UI_API XmlConverter
            : public virtual node::XmlConverter
        {
        public:
            XmlValue toXml(const Node *const value) const override;
            Node *fromXml(const XmlValue &xml) const override;

            XmlConverter() = default;
            virtual ~XmlConverter() = default;
        };

        extern XmlConverter CACTO_UI_API Converter;

    }

}

#endif