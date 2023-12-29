#pragma once

#include <Cacto/UI/Span.hpp>
#include <Cacto/UI/Block.hpp>

namespace cacto
{

    class CACTO_UI_API Label
        : public Block
    {

    public:
        using Anchor = Box::Anchor;

        Anchor getHorizontalAnchor() const;
        Label &setHorizontalAnchor(Anchor value);

        Anchor getVerticalAnchor() const;
        Label &setVerticalAnchor(Anchor value);

        const Span &asSpan() const;
        Span &asSpan();

        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Vector2f compact() override;
        sf::Vector2f inflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void place(const sf::Vector2f &position = {0, 0}) override;

        Label();
        virtual ~Label();

    private:
        Span m_span;
        Anchor m_hAnchor;
        Anchor m_vAnchor;
    };

    XmlValue CACTO_UI_API toXml(const Label &label);
    void CACTO_UI_API fromXml(Label &label, const XmlValue &xml);

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
