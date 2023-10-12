#ifndef CACTO_OBJECT_INL
#define CACTO_OBJECT_INL

#include <Cacto/Core/Object.hpp>

namespace cacto
{

    template <typename T>
    inline std::shared_ptr<T> Object::as()
    {
        auto shared = shared_from_this();
        auto self = std::dynamic_pointer_cast<T>(shared);
        return self;
    }

}

#endif