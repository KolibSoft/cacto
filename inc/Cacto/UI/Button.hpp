#pragma once

#include <Cacto/Window/EventListener.hpp>
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
        Button &&setLeft(f32t value, bool resize = false);
        Button &&setRight(f32t value, bool resize = false);
        Button &&setTop(f32t value, bool resize = false);
        Button &&setBottom(f32t value, bool resize = false);

        Button &&setWidth(f32t value, BoxAnchor anchor = BoxAnchor::Start);
        Button &&setHeight(f32t value, BoxAnchor anchor = BoxAnchor::Start);

        Button &&shrink(const Thickness &thickness);
        Button &&expand(const Thickness &thickness);

        Button &&setBackground(Node *const value);
        Button &&setBackground(Node &&value);

        Button &&setMargin(const Thickness &value);
        Button &&setPadding(const Thickness &value);

        Button &&setMinWidth(f32t value);
        Button &&setMaxWidth(f32t value);
        Button &&setMinHeight(f32t value);
        Button &&setMaxHeight(f32t value);

        Button &&setFixedWidth(f32t value);
        Button &&setFixedHeight(f32t value);

        Button &&setFont(const sf::Font *const value);
        Button &&setString(const sf::String &value);
        Button &&setDirection(TextDirection value);
        Button &&setCharacterSize(u32t value);
        Button &&setColor(const sf::Color &value);
        Button &&setHorizontalAnchor(BoxAnchor value);
        Button &&setVerticalAnchor(BoxAnchor value);

        const EventListener &getOnClickListener() const;
        Button &&setOnClickListener(const EventListener &value);

        Button &&setId(const std::string &value);

        Button *clone() const override;
        Button *acquire() override;

        bool handle(const sf::Event &event) override;

        void click(sf::Mouse::Button button = sf::Mouse::Left, const sf::Vector2f &position = {0, 0}) override;
        void focus() override;
        void unfocus() override;

        Button();
        virtual ~Button();

        Button(const Button &other);
        Button &operator=(const Button &other);

        Button(Button &&other);
        Button &operator=(Button &&other);

    protected:
        void clone(const Button &other);
        void acquire(Button &&other);

        virtual void onClick(const sf::Event &event);

    private:
        EventListener m_onClick;
        bool m_focused;
    };

    XmlValue CACTO_UI_API toXml(const Button &button);
    Button CACTO_UI_API toButton(const XmlValue &xml);

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
