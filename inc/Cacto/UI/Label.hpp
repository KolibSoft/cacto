#pragma once

#include <Cacto/UI/Span.hpp>
#include <Cacto/UI/Block.hpp>

namespace cacto
{

    class CACTO_UI_API Label
        : public Block
    {

    public:
        Label &&setLeft(f32t value, bool resize = false);
        Label &&setRight(f32t value, bool resize = false);
        Label &&setTop(f32t value, bool resize = false);
        Label &&setBottom(f32t value, bool resize = false);

        Label &&setWidth(f32t value, BoxAnchor anchor = BoxAnchor::Start);
        Label &&setHeight(f32t value, BoxAnchor anchor = BoxAnchor::Start);

        Label &&shrink(const Thickness &thickness);
        Label &&expand(const Thickness &thickness);

        Label &&setBackground(Reference<Node> value);

        Label &&setMargin(const Thickness &value);
        Label &&setPadding(const Thickness &value);

        Label &&setMinWidth(f32t value);
        Label &&setMaxWidth(f32t value);
        Label &&setMinHeight(f32t value);
        Label &&setMaxHeight(f32t value);

        Label &&setFixedWidth(f32t value);
        Label &&setFixedHeight(f32t value);

        operator const Span &() const;
        operator Span &();

        const sf::Font *const getFont() const;
        Label &&setFont(const sf::Font *const value);

        const sf::String &getString() const;
        Label &&setString(const sf::String &value);

        TextDirection getDirection() const;
        Label &&setDirection(TextDirection value);

        u32t getCharacterSize() const;
        Label &&setCharacterSize(u32t value);

        const sf::Color &getColor() const;
        Label &&setColor(const sf::Color &value);

        BoxAnchor getHorizontalAnchor() const;
        Label &&setHorizontalAnchor(BoxAnchor value);

        BoxAnchor getVerticalAnchor() const;
        Label &&setVerticalAnchor(BoxAnchor value);

        Label &&setId(const std::string &value);

        Label *clone() const override;
        Label *acquire() override;

        sf::Vector2f compact() override;
        sf::Vector2f inflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void place(const sf::Vector2f &position = {0, 0}) override;

        Label();
        virtual ~Label();

        Label(const Label &other);
        Label &operator=(const Label &other);

        Label(Label &&other);
        Label &operator=(Label &&other);

    protected:
        void clone(const Label &other);
        void acquire(Label &&other);

        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        Span m_span;
        BoxAnchor m_hAnchor;
        BoxAnchor m_vAnchor;
    };

    XmlValue CACTO_UI_API toXml(const Label &label);
    Label CACTO_UI_API toLabel(const XmlValue &xml);

    namespace label
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
