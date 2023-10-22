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

            sf::Vector2f boxSize;
        };

        RowHolder *onHold(Node &child) const override;

        sf::Vector2f onCompact(const sf::Vector2f &contentSize = {0, 0}) override;
        sf::Vector2f onInflate(const sf::Vector2f &containerSize = {0, 0}) override;
        void onPlace(const sf::Vector2f &position = {0, 0}) override;
    };

}

#endif