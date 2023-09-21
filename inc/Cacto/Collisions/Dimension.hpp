#ifndef CACTO_DIMENSION_HPP
#define CACTO_DIMENSION_HPP

#include <functional>
#include <Cacto/Collisions/Export.hpp>

namespace sf
{

    template <typename T>
    class Rect;

    using FloatRect = Rect<cacto::f32t>;

}

namespace cacto
{

    class Body;

    class CACTO_COLLISIONS_API Dimension
    {

    public:
        Dimension() = default;
        virtual ~Dimension() = default;
    };

}

#endif