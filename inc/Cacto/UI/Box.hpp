#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <Cacto/Lang/Object.hpp>
#include <Cacto/UI/Export.hpp>

namespace cacto
{

    class Thickness;

    class CACTO_UI_API Box
        : public Object
    {

    public:
        enum Anchor
        {
            Start,
            End,
            Center
        };

        f32t getLeft() const;
        void setLeft(f32t value, bool resize = false);

        f32t getRight() const;
        void setRight(f32t value, bool resize = false);

        f32t getTop() const;
        void setTop(f32t value, bool resize = false);

        f32t getBottom() const;
        void setBottom(f32t value, bool resize = false);

        f32t getWidth() const;
        void setWidth(f32t value, Anchor anchor = Start);

        f32t getHeight() const;
        void setHeight(f32t value, Anchor anchor = Start);

        void shrink(const Thickness &thickness);
        void expand(const Thickness &thickness);

        bool contains(const sf::Vector2f &point) const;

        Box(const sf::FloatRect &rect = {});
        operator const sf::FloatRect &() const;

        virtual ~Box();

    private:
        sf::FloatRect m_rect;
    };

}
