#include <Cacto/Lang/Object.hpp>

namespace cacto
{

    template <typename T>
    inline Shared<const T> Object::as() const
    {
        try
        {
            auto self = shared_from_this();
            auto cast = std::dynamic_pointer_cast<const T>(self);
            return cast;
        }
        catch (std::bad_cast)
        {
            return nullptr;
        }
    }

    template <typename T>
    inline Shared<T> Object::as()
    {
        try
        {
            auto self = shared_from_this();
            auto cast = std::dynamic_pointer_cast<T>(self);
            return cast;
        }
        catch (std::bad_cast)
        {
            return nullptr;
        }
    }

}