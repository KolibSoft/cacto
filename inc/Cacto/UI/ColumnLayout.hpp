#ifndef CACTO_COLUMN_LAYOUT_HPP
#define CACTO_COLUMN_LAYOUT_HPP

#include <vector>
#include <Cacto/UI/Layout.hpp>
#include <Cacto/UI/Block.hpp>

namespace cacto
{

    namespace column_layout
    {
        class Holder;
    }

    class CACTO_UI_API ColumnLayout
        : public Block
    {

    public:
        using Holder = column_layout::Holder;

        enum Direction
        {
            Forward,
            Reverse
        };

        szt getChildCount() const override;
        Node *const getChild(szt index = 0) const override;

        BoxAnchor getHorizontalAnchor(const Node &child) const;
        BoxAnchor getHorizontalAnchor(Node &&child) const = delete;

        ColumnLayout &setHorizontalAnchor(Node &child, BoxAnchor value);

        BoxAnchor getVerticalAnchor() const;
        ColumnLayout &setVerticalAnchor(BoxAnchor value);

        Direction getDirection() const;
        ColumnLayout &setDirection(Direction value);

        f32t getHorizontalWeight(const Node &child) const;
        f32t getHorizontalWeight(Node &&child) const = delete;

        ColumnLayout &setHorizontalWeight(Node &child, f32t value);

        f32t getVerticalWeight(const Node &child) const;
        f32t getVerticalWeight(Node &&child) const = delete;

        ColumnLayout &setVerticalWeight(Node &child, f32t value);

        Holder &append(Node &child);
        void remove(Node &child);

        ColumnLayout();
        virtual ~ColumnLayout();

        ColumnLayout(const ColumnLayout &other);
        ColumnLayout &operator=(const ColumnLayout &other);

    protected:
        void onAppend(Node &child) override;
        void onRemove(Node &child) override;

        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Vector2f onCompact() override;
        sf::Vector2f onInflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void onPlace(const sf::Vector2f &position = {0, 0}) override;

    private:
        BoxAnchor m_vAnchor;
        Direction m_direction;
        f32t m_length;
        std::vector<Holder> m_holders;
    };

    namespace column_layout
    {
        class Holder
            : public layout::Holder
        {
        public:
            ColumnLayout::Anchor getHorizontalAnchor() const;
            Holder &setHorizontalAnchor(ColumnLayout::Anchor value);

            f32t getHorizontalWeight() const;
            Holder &setHorizontalWeight(f32t value);

            f32t getVerticalWeight() const;
            Holder &setVerticalWeight(f32t value);

            Holder(Node &node);
            virtual ~Holder();

        private:
            RowLayout::Anchor m_hAnchor;
            f32t m_hWeight;
            f32t m_vWeight;
        };
    }

}

#endif