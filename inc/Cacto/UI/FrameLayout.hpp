#ifndef CACTO_FRAME_LAYOUT_HPP
#define CACTO_FRAME_LAYOUT_HPP

#include <Cacto/UI/Layout.hpp>

namespace cacto
{

    class CACTO_UI_API FrameLayout
        : public Layout
    {

    public:
        Anchor getHorizontalAnchor(const Node &child) const;
        Anchor getHorizontalAnchor(Node &&child) const = delete;

        void setHorizontalAnchor(Node &child, Anchor value);

        Anchor getVerticalAnchor(const Node &child) const;
        Anchor getVerticalAnchor(Node &&child) const = delete;

        void setVerticalAnchor(Node &child, Anchor value);

        FrameLayout();
        virtual ~FrameLayout();

        FrameLayout(const FrameLayout &other);
        FrameLayout &operator=(const FrameLayout &other);

    protected:
        Holder *onHold(Node &child) const override;

        void onAppend(Node &child) override;
        void onRemove(Node &child) override;

        sf::Vector2f onCompact(const sf::Vector2f &contentSize = {0, 0}) override;
        sf::Vector2f onInflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void onPlace(const sf::Vector2f &position = {0, 0}) override;

        class FrameHolder
            : public Holder
        {

        public:
            FrameHolder(Node &child);
            virtual ~FrameHolder();

            Anchor hAnchor;
            Anchor vAnchor;
            sf::Vector2f boxSize;
        };
        
    };

}

#endif