#ifndef CACTO_COLUMN_LAYOUT_HPP
#define CACTO_COLUMN_LAYOUT_HPP

#include <vector>
#include <Cacto/UI/Layout.hpp>

namespace cacto
{

    class CACTO_UI_API ColumnLayout
        : public Layout
    {

    public:
        Anchor getHorizontalAnchor(const Node &child) const;
        Anchor getHorizontalAnchor(Node &&child) const = delete;

        void setHorizontalAnchor(Node &child, Anchor value);

        Anchor getVerticalAnchor() const;
        void setVerticalAnchor(Anchor value);

        Direction getDirection() const;
        void setDirection(Direction value);

        ColumnLayout();
        virtual ~ColumnLayout();

        ColumnLayout(const ColumnLayout &other);
        ColumnLayout &operator=(const ColumnLayout &other);

    protected:
        class ColumnHolder
            : public Holder
        {
        public:
            ColumnHolder(Node &child);
            virtual ~ColumnHolder();

            Anchor hAnchor;
            sf::Vector2f boxSize;
        };

        ColumnHolder *onHold(Node &child) const override;

        sf::Vector2f onCompact(const sf::Vector2f &contentSize = {0, 0}) override;
        sf::Vector2f onInflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void onPlace(const sf::Vector2f &position = {0, 0}) override;

    private:
        Anchor m_vAnchor;
        Direction m_direction;
        f32t m_length;
    };

}

#endif