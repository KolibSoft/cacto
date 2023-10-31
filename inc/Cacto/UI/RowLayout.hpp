#ifndef CACTO_ROW_LAYOUT_HPP
#define CACTO_ROW_LAYOUT_HPP

#include <vector>
#include <Cacto/UI/Layout.hpp>

namespace cacto
{

    class CACTO_UI_API RowLayout
        : public Layout
    {

    public:
        Anchor getVerticalAnchor(const Node &child) const;
        Anchor getVerticalAnchor(Node &&child) const = delete;

        void setVerticalAnchor(Node &child, Anchor value);

        Anchor getHorizontalAnchor() const;
        void setHorizontalAnchor(Anchor value);

        Direction getDirection() const;
        void setDirection(Direction value);

        f32t getHorizontalWeight(const Node &child) const;
        f32t getHorizontalWeight(Node &&child) const = delete;

        void setHorizontalWeight(Node &child, f32t value);

        f32t getVerticalWeight(const Node &child) const;
        f32t getVerticalWeight(Node &&child) const = delete;

        void setVerticalWeight(Node &child, f32t value);

        RowLayout();
        virtual ~RowLayout();

        RowLayout(const RowLayout &other);
        RowLayout &operator=(const RowLayout &other);

    protected:
        class RowHolder
            : public Holder
        {
        public:
            RowHolder(Node &child);
            virtual ~RowHolder();

            Anchor vAnchor;
            f32t hWeight;
            f32t vWeight;
            sf::Vector2f boxSize;
        };

        RowHolder *onHold(Node &child) const override;

        sf::Vector2f onCompact(const sf::Vector2f &contentSize = {0, 0}) override;
        sf::Vector2f onInflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void onPlace(const sf::Vector2f &position = {0, 0}) override;

    private:
        Anchor m_hAnchor;
        Direction m_direction;
        f32t m_length;
    };

}

#endif