#pragma once

#include <utility>
#include <Cacto/UI/Thickness.hpp>

namespace cacto
{

    inline Thickness Thickness::operator+(const Thickness &other) const
    {
        return Thickness(*this).add(other);
    }

    inline Thickness &Thickness::operator+=(const Thickness &other)
    {
        return add(other);
    }

    inline Thickness Thickness::operator-(const Thickness &other) const
    {
        return Thickness(*this).subtract(other);
    }

    inline Thickness &Thickness::operator-=(const Thickness &other)
    {
        return subtract(other);
    }

    inline Thickness Thickness::operator*(f32t factor) const
    {
        return Thickness(*this).multiply(factor);
    }

    inline Thickness &Thickness::operator*=(f32t factor)
    {
        return multiply(factor);
    }

    inline Thickness Thickness::operator/(f32t factor) const
    {
        return Thickness(*this).divide(factor);
    }

    inline Thickness &Thickness::operator/=(f32t factor)
    {
        return divide(factor);
    }

}