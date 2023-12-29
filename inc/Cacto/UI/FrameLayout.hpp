#pragma once

#include <Cacto/UI/Block.hpp>

namespace cacto
{

    class CACTO_UI_API FrameLayout
        : public Block,
          public virtual ParentNode
    {

    public:
        Anchor getHorizontalAnchor() const;
        FrameLayout &setHorizontalAnchor(Anchor value);

        Anchor getVerticalAnchor() const;
        FrameLayout &setVerticalAnchor(Anchor value);

        ParentNode *const getParent() const override;

        szt getChildCount() const override;
        ChildNode *const getChild(szt index = 0) const override;

        void append(ChildNode &child) override;
        void remove(ChildNode &child) override;

        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Vector2f compact() override;
        sf::Vector2f inflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void place(const sf::Vector2f &position = {0, 0}) override;

        FrameLayout();
        virtual ~FrameLayout();

    protected:
        const Box &getChildBox() const;

    private:
        Anchor m_hAnchor;
        Anchor m_vAnchor;
        Box m_childBox;
        ChildNode *m_child;
    };

    XmlValue CACTO_UI_API toXml(const FrameLayout &frame);
    void CACTO_UI_API fromXml(FrameLayout &frame, const XmlValue &xml);

    namespace frame
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
