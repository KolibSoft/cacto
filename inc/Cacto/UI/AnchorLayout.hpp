#ifndef CACTO_ANCHOR_LAYOUT_HPP
#define CACTO_ANCHOR_LAYOUT_HPP

#include <vector>
#include <Cacto/UI/Layout.hpp>

namespace cacto
{

    class CACTO_UI_API AnchorLayout
        : public Layout
    {

    public:
        Anchor getHorizontalAnchor(const Node &child) const;
        Anchor getHorizontalAnchor(Node &&child) const = delete;

        void setHorizontalAnchor(Node &child, Anchor value);

        Anchor getVerticalAnchor(const Node &child) const;
        Anchor getVerticalAnchor(Node &&child) const = delete;

        void setVerticalAnchor(Node &child, Anchor value);

        AnchorLayout();
        virtual ~AnchorLayout();

        AnchorLayout(const AnchorLayout &other);
        AnchorLayout &operator=(const AnchorLayout &other);

    protected:

        class AnchorHolder
            : public Holder
        {

        public:
            AnchorHolder(Node &child);
            virtual ~AnchorHolder();

            Anchor hAnchor;
            Anchor vAnchor;
            sf::Vector2f boxSize;
        };

        AnchorHolder *onHold(Node &child) const override;

        sf::Vector2f onInflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void onPlace(const sf::Vector2f &position = {0, 0}) override;
    };

}

#endif