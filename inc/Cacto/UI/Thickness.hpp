#ifndef CACTO_THICKNESS_HPP
#define CACTO_THICKNESS_HPP

#include <Cacto/UI/Export.hpp>

namespace cacto
{

    class CACTO_UI_API Thickness
    {

    public:
        static const Thickness Default;

        f32t getHorizontal() const;
        f32t getVertical() const;

        Thickness &add(const Thickness &other);
        Thickness &subtract(const Thickness &other);
        Thickness &multiply(f32t factor);
        Thickness &divide(f32t factor);

        Thickness(f32t value = 0);
        Thickness(f32t horizontal, f32t vertical);
        Thickness(f32t _left, f32t _top, f32t _right, f32t _bottom);

        f32t left;
        f32t top;
        f32t right;
        f32t bottom;
    };

}

#endif