#pragma once

#include <Cacto/Core/ParentNode.hpp>
#include <Cacto/UI/Block.hpp>

namespace cacto
{

    class CACTO_UI_API FrameLayout
        : public Block,
          public virtual ParentNode
    {

    public:
        FrameLayout &&setLeft(f32t value, bool resize = false);
        FrameLayout &&setRight(f32t value, bool resize = false);
        FrameLayout &&setTop(f32t value, bool resize = false);
        FrameLayout &&setBottom(f32t value, bool resize = false);

        FrameLayout &&setWidth(f32t value, BoxAnchor anchor = BoxAnchor::Start);
        FrameLayout &&setHeight(f32t value, BoxAnchor anchor = BoxAnchor::Start);

        FrameLayout &&shrink(const Thickness &thickness);
        FrameLayout &&expand(const Thickness &thickness);

        FrameLayout &&setBackground(Node *const value);
        FrameLayout &&setBackground(Node &&value);

        FrameLayout &&setMargin(const Thickness &value);
        FrameLayout &&setPadding(const Thickness &value);

        FrameLayout &&setMinWidth(f32t value);
        FrameLayout &&setMaxWidth(f32t value);
        FrameLayout &&setMinHeight(f32t value);
        FrameLayout &&setMaxHeight(f32t value);

        FrameLayout &&setFixedWidth(f32t value);
        FrameLayout &&setFixedHeight(f32t value);

        BoxAnchor getHorizontalAnchor() const;
        FrameLayout &&setHorizontalAnchor(BoxAnchor value);

        BoxAnchor getVerticalAnchor() const;
        FrameLayout &&setVerticalAnchor(BoxAnchor value);

        FrameLayout &&setId(const std::string &value);
        Node *const getParent() const override;

        FrameLayout *clone() const override;
        FrameLayout *acquire() override;

        szt getChildCount() const override;
        ChildNode *const getChild(szt index = 0) const override;

        void append(ChildNode &child) override;
        FrameLayout &&append(ChildNode &&child);

        void remove(ChildNode &child) override;

        sf::Vector2f compact() override;
        sf::Vector2f inflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void place(const sf::Vector2f &position = {0, 0}) override;

        FrameLayout();
        virtual ~FrameLayout();

        FrameLayout(const FrameLayout &other);
        FrameLayout &operator=(const FrameLayout &other);

        FrameLayout(FrameLayout &&other);
        FrameLayout &operator=(FrameLayout &&other);

    protected:
        void clone(const FrameLayout &other);
        void acquire(FrameLayout &&other);

        const Box &getChildBox() const;

        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        BoxAnchor m_hAnchor;
        BoxAnchor m_vAnchor;
        Box m_childBox;
        ChildNode *m_child;
        bool m_childOwned;
    };

    XmlValue CACTO_UI_API toXml(const FrameLayout &frame);
    FrameLayout CACTO_UI_API toFrameLayout(const XmlValue &xml);

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
