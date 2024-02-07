#ifndef CACTO_ANCHOR_LAYOUT_HPP
#define CACTO_ANCHOR_LAYOUT_HPP

#include <vector>
#include <Cacto/UI/Layout.hpp>
#include <Cacto/UI/Block.hpp>

namespace cacto
{

    namespace anchor_layout
    {
        class Holder;
    }

    class CACTO_UI_API AnchorLayout
        : public Block
    {

    public:
        using Holder = anchor_layout::Holder;

        szt getChildCount() const override;
        Node *const getChild(szt index = 0) const override;

        BoxAnchor getHorizontalAnchor(const Node &child) const;
        BoxAnchor getHorizontalAnchor(Node &&child) const = delete;

        AnchorLayout &setHorizontalAnchor(Node &child, BoxAnchor value);

        BoxAnchor getVerticalAnchor(const Node &child) const;
        BoxAnchor getVerticalAnchor(Node &&child) const = delete;

        AnchorLayout &setVerticalAnchor(Node &child, BoxAnchor value);

        f32t getHorizontalWeight(const Node &child) const;
        f32t getHorizontalWeight(Node &&child) const = delete;

        AnchorLayout &setHorizontalWeight(Node &child, f32t value);

        f32t getVerticalWeight(const Node &child) const;
        f32t getVerticalWeight(Node &&child) const = delete;

        AnchorLayout &setVerticalWeight(Node &child, f32t value);

        Holder &append(Node &child);
        void remove(Node &child);

        AnchorLayout();
        virtual ~AnchorLayout();

        AnchorLayout(const AnchorLayout &other);
        AnchorLayout &operator=(const AnchorLayout &other);

    protected:
        void onAppend(Node &child) override;
        void onRemove(Node &child) override;

        void onDraw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

        sf::Vector2f onInflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void onPlace(const sf::Vector2f &position = {0, 0}) override;

    private:
        std::vector<Holder> m_holders;
    };

    namespace anchor_layout
    {

        class Holder
            : public layout::Holder
        {

        public:
            AnchorLayout::Anchor getHorizontalAnchor() const;
            Holder &setHorizontalAnchor(AnchorLayout::Anchor value);

            AnchorLayout::Anchor getVerticalAnchor() const;
            Holder &setVerticalAnchor(AnchorLayout::Anchor value);

            f32t getHorizontalWeight() const;
            Holder &setHorizontalWeight(f32t value);

            f32t getVerticalWeight() const;
            Holder &setVerticalWeight(f32t value);

            Holder(Node &node);
            virtual ~Holder();

        private:
            AnchorLayout::Anchor m_hAnchor;
            AnchorLayout::Anchor m_vAnchor;
            f32t m_hWeight;
            f32t m_vWeight;
        };

    }

}

#endif