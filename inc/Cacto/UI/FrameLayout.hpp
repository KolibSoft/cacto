#ifndef CACTO_FRAME_LAYOUT_HPP
#define CACTO_FRAME_LAYOUT_HPP

#include <Cacto/UI/Layout.hpp>
#include <Cacto/UI/Block.hpp>

namespace cacto
{

    class CACTO_UI_API FrameLayout
        : public Block
    {

    public:
        szt getChildCount() const override;
        Node *const getChild(szt index = 0) const override;

        Anchor getHorizontalAnchor() const;
        FrameLayout &setHorizontalAnchor(Anchor value);

        Anchor getVerticalAnchor() const;
        FrameLayout &setVerticalAnchor(Anchor value);

        void append(Node &child);
        void remove(Node &child);

        FrameLayout();
        virtual ~FrameLayout();

        FrameLayout(const FrameLayout &other);
        FrameLayout &operator=(const FrameLayout &other);

    protected:
        using Holder = layout::Holder;

        const Holder *const getHolder() const;
        Holder *const getHolder();

        void onAppend(Node &child) override;
        void onRemove(Node &child) override;

        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Vector2f onCompact() override;
        sf::Vector2f onInflate(const sf::Vector2f &containerSize) override;
        void onPlace(const sf::Vector2f &position) override;

    private:
        Anchor m_hAnchor;
        Anchor m_vAnchor;
        Holder *m_holder;
    };

}

#endif