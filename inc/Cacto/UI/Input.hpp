#pragma once

#include <SFML/System/String.hpp>
#include <Cacto/Window/EventListener.hpp>
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

        bool handle(const sf::Event &event) override;

        void input(u32t unicode) override;
        void focus() override;
        void unfocus() override;

        Input();
        virtual ~Input();

    protected:
        virtual void onInput(const sf::Event &event);

    private:
        EventListener m_onInput;
        bool m_focused;
    };

    XmlValue CACTO_UI_API toXml(const Input &input);
    void CACTO_UI_API fromXml(Input &input, const XmlValue &xml);

    namespace input
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
