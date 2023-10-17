#ifndef CACTO_BOX_HPP
#define CACTO_BOX_HPP

#include <SFML/Graphics/Rect.hpp>
#include <Cacto/UI/Export.hpp>

namespace cacto
{

    class Thickness;

    class CACTO_UI_API Box
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

        sf::FloatRect getBounds() const;
        bool contains(const sf::Vector2f &point) const;

        Box(f32t width, f32t height);
        Box(f32t left, f32t top, f32t width, f32t height);
        Box();
        virtual ~Box();

    private:
        f32t m_left;
        f32t m_top;
        f32t m_width;
        f32t m_height;
    };

}

#endif