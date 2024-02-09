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
        Input &&setLeft(f32t value, bool resize = false);
        Input &&setRight(f32t value, bool resize = false);
        Input &&setTop(f32t value, bool resize = false);
        Input &&setBottom(f32t value, bool resize = false);

        Input &&setWidth(f32t value, BoxAnchor anchor = BoxAnchor::Start);
        Input &&setHeight(f32t value, BoxAnchor anchor = BoxAnchor::Start);

        Input &&shrink(const Thickness &thickness);
        Input &&expand(const Thickness &thickness);

        Input &&setBackground(Reference<Node> value);

        Input &&setMargin(const Thickness &value);
        Input &&setPadding(const Thickness &value);

        Input &&setMinWidth(f32t value);
        Input &&setMaxWidth(f32t value);
        Input &&setMinHeight(f32t value);
        Input &&setMaxHeight(f32t value);

        Input &&setFixedWidth(f32t value);
        Input &&setFixedHeight(f32t value);

        Input &&setFont(const sf::Font *const value);
        Input &&setString(const sf::String &value);
        Input &&setDirection(TextDirection value);
        Input &&setCharacterSize(u32t value);
        Input &&setColor(const sf::Color &value);
        Input &&setHorizontalAnchor(BoxAnchor value);
        Input &&setVerticalAnchor(BoxAnchor value);

        const EventListener &getOnInputListener() const;
        Input &&setOnInputListener(const EventListener &value);

        Input &&setId(const std::string &value);

        Input *clone() const override;
        Input *acquire() override;

        bool handle(const sf::Event &event) override;

        void input(u32t unicode) override;
        void focus() override;
        void unfocus() override;

        Input();
        virtual ~Input();

        Input(const Input &other);
        Input &operator=(const Input &other);

        Input(Input &&other);
        Input &operator=(Input &&other);

    protected:
        void clone(const Input &other);
        void acquire(Input &&other);

        virtual void onInput(const sf::Event &event);

    private:
        EventListener m_onInput;
        bool m_focused;
    };

    XmlValue CACTO_UI_API toXml(const Input &input);
    Input CACTO_UI_API toInput(const XmlValue &xml);

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
