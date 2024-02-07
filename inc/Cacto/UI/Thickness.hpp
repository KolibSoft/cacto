#pragma once

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
        inline Thickness operator+(const Thickness &other) const;
        inline Thickness &operator+=(const Thickness &other);

        Thickness &subtract(const Thickness &other);
        inline Thickness operator-(const Thickness &other) const;
        inline Thickness &operator-=(const Thickness &other);

        Thickness &multiply(f32t factor);
        inline Thickness operator*(f32t factor) const;
        inline Thickness &operator*=(f32t factor);

        Thickness &divide(f32t factor);
        inline Thickness operator/(f32t factor) const;
        inline Thickness &operator/=(f32t factor);

        Thickness(f32t value = 0);
        Thickness(f32t horizontal, f32t vertical);
        Thickness(f32t _left, f32t _top, f32t _right, f32t _bottom);

        f32t left;
        f32t top;
        f32t right;
        f32t bottom;
    };

    std::string CACTO_UI_API toString(const Thickness &thickness);
    Thickness CACTO_UI_API toTickness(const std::string &string);

}

#include <Cacto/UI/Thickness.inl>