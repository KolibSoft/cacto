#ifndef CACTO_FRAME_LAYOUT_HPP
#define CACTO_FRAME_LAYOUT_HPP

#include <Cacto/UI/Block.hpp>
#include <Cacto/UI/Export.hpp>

namespace cacto
{

    class CACTO_UI_API FrameLayout
        : public Block
    {

    public:
        szt getChildCount() const override;
        SharedNode getChild(szt index = 0) const override;

        void append(const SharedNode &child);
        void remove(const SharedNode &child);

        Anchor getHorizontalAnchor(const SharedNode &child) const;
        void setHorizontalAnchor(const SharedNode &child, Anchor value);

        Anchor getVerticalAnchor(const SharedNode &child) const;
        void setVerticalAnchor(const SharedNode &child, Anchor value);

        FrameLayout();
        virtual ~FrameLayout();

    protected:
        struct Holder;
        using SharedHolder = std::shared_ptr<Holder>;

        void onAppend(const SharedNode &child) override;
        void onRemove(const SharedNode &child) override;

        bool onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Vector2f onCompact(const sf::Vector2f &contentSize = {0, 0}) override;
        sf::Vector2f onInflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void onPlace(const sf::Vector2f &position = {0, 0}) override;

        struct Holder
        {

        public:
            Holder() = default;
            virtual ~Holder() = default;

            SharedNode child;
            Anchor hAnchor;
            Anchor vAnchor;
            sf::Vector2f boxSize;
        };

    private:
        SharedHolder m_holder;
    };

}

#endif