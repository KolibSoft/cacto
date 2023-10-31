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

        f32t getHorizontalWeight(const Node &child) const;
        f32t getHorizontalWeight(Node &&child) const = delete;

        void setHorizontalWeight(Node &child, f32t value);

        f32t getVerticalWeight(const Node &child) const;
        f32t getVerticalWeight(Node &&child) const = delete;

        void setVerticalWeight(Node &child, f32t value);

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
            f32t hWeight;
            f32t vWeight;
            sf::Vector2f boxSize;
        };

        AnchorHolder *onHold(Node &child) const override;

        sf::Vector2f onInflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void onPlace(const sf::Vector2f &position = {0, 0}) override;
    };

}

#endif