#include <Cacto/UI/Thickness.hpp>

namespace cacto
{

    const Thickness Thickness::Default(0);

    f32t Thickness::getHorizontal() const
    {
        return left + right;
    }

    f32t Thickness::getVertical() const
    {
        return top + bottom;
    }

    Thickness &Thickness::add(const Thickness &other)
    {
        left += other.left;
        top += other.top;
        right += other.right;
        bottom += other.bottom;
        return *this;
    }

    Thickness &Thickness::subtract(const Thickness &other)
    {
        left -= other.left;
        top -= other.top;
        right -= other.right;
        bottom -= other.bottom;
        return *this;
    }

    Thickness &Thickness::multiply(f32t factor)
    {
        left *= factor;
        top *= factor;
        right *= factor;
        bottom *= factor;
        return *this;
    }

    Thickness &Thickness::divide(f32t factor)
    {
        left /= factor;
        top /= factor;
        right /= factor;
        bottom /= factor;
        return *this;
    }

    Thickness::Thickness(f32t value)
        : left(value), top(value), right(value), bottom(value)
    {
    }

    Thickness::Thickness(f32t horizontal, f32t vertical)
        : left(horizontal), top(vertical), right(horizontal), bottom(vertical)
    {
    }

    Thickness::Thickness(f32t _left, f32t _top, f32t _right, f32t _bottom)
        : left(_left), top(_top), right(_right), bottom(_bottom)
    {
    }

}