#pragma once

#include <Cacto/Core/Morph.hpp>

namespace cacto
{

    template <typename T>
    inline const T &Morph::ref() const
    {
        auto &cast = dynamic_cast<const T &>(*this);
        return cast;
    }

    template <typename T>
    inline T &Morph::ref()
    {
        auto &cast = dynamic_cast<T &>(*this);
        return cast;
    }

    template <typename T>
    inline const T *Morph::ptr() const
    {
        auto *cast = dynamic_cast<const T *>(this);
        return cast;
    }

    template <typename T>
    inline T *Morph::ptr()
    {
        auto *cast = dynamic_cast<T *>(this);
        return cast;
    }

}