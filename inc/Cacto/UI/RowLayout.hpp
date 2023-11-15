#ifndef CACTO_ROW_LAYOUT_HPP
#define CACTO_ROW_LAYOUT_HPP

#include <vector>
#include <Cacto/UI/Layout.hpp>
#include <Cacto/UI/Block.hpp>

namespace cacto
{

    namespace row_layout
    {
        class Holder;
    }

    class CACTO_UI_API RowLayout
        : public Block
    {

    public:
        using Holder = row_layout::Holder;

        enum Direction
        {
            Forward,
            Reverse
        };

        szt getChildCount() const override;
        Node *const getChild(szt index = 0) const override;

        Anchor getVerticalAnchor(const Node &child) const;
        Anchor getVerticalAnchor(Node &&child) const = delete;

        RowLayout &setVerticalAnchor(Node &child, Anchor value);

        Anchor getHorizontalAnchor() const;
        RowLayout &setHorizontalAnchor(Anchor value);

        Direction getDirection() const;
        RowLayout &setDirection(Direction value);

        f32t getHorizontalWeight(const Node &child) const;
        f32t getHorizontalWeight(Node &&child) const = delete;

        RowLayout &setHorizontalWeight(Node &child, f32t value);

        f32t getVerticalWeight(const Node &child) const;
        f32t getVerticalWeight(Node &&child) const = delete;

        RowLayout &setVerticalWeight(Node &child, f32t value);

        Holder &append(Node &child);
        void remove(Node &child);

        RowLayout();
        virtual ~RowLayout();

        RowLayout(const RowLayout &other);
        RowLayout &operator=(const RowLayout &other);

    protected:
        void onAppend(Node &child) override;
        void onRemove(Node &child) override;

        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Vector2f onCompact() override;
        sf::Vector2f onInflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void onPlace(const sf::Vector2f &position = {0, 0}) override;

    private:
        Anchor m_hAnchor;
        Direction m_direction;
        f32t m_length;
        std::vector<Holder> m_holders;
    };

    namespace row_layout
    {
        class Holder
            : public layout::Holder
        {
        public:
            RowLayout::Anchor getVerticalAnchor() const;
            Holder &setVerticalAnchor(RowLayout::Anchor value);

            f32t getHorizontalWeight() const;
            Holder &setHorizontalWeight(f32t value);

            f32t getVerticalWeight() const;
            Holder &setVerticalWeight(f32t value);

            Holder(Node &node);
            virtual ~Holder();

        private:
            RowLayout::Anchor m_vAnchor;
            f32t m_hWeight;
            f32t m_vWeight;
        };
    }

}

#endif