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

        f32t getHorizontalWeight(const Node &child) const;
        f32t getHorizontalWeight(Node &&child) const = delete;

        void setHorizontalWeight(Node &child, f32t value);

        f32t getVerticalWeight(const Node &child) const;
        f32t getVerticalWeight(Node &&child) const = delete;

        void setVerticalWeight(Node &child, f32t value);

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
            f32t hWeight;
            f32t vWeight;
            sf::Vector2f size;
        };

        ColumnHolder *onHold(Node &child) const override;

        sf::Vector2f onCompact() override;
        sf::Vector2f onInflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void onPlace(const sf::Vector2f &position = {0, 0}) override;

    private:
        Anchor m_vAnchor;
        Direction m_direction;
        f32t m_length;
    };

}

#endif