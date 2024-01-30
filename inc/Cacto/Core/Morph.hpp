#pragma once

namespace cacto
{

    class Morph
    {

    public:
        template <typename T>
        const T &ref() const;

        template <typename T>
        T &ref();

        template <typename T>
        const T *ptr() const;

        template <typename T>
        T *ptr();

        Morph() = default;
        virtual ~Morph() = default;
    };

}

#include <Cacto/Core/Morph.inl>