#ifndef CACTO_FRAME_LAYOUT_HPP
#define CACTO_FRAME_LAYOUT_HPP

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

    private:
        Anchor m_hAnchor;
        Anchor m_vAnchor;
        sf::Vector2f m_childSize;
        ChildNode *m_child;
    };

}

#endif