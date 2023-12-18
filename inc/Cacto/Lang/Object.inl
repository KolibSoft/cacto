#include <Cacto/Lang/Object.hpp>

namespace cacto
{

    template <typename T>
    inline Shared<const T> Object::as() const
    {
        try
        {
            auto cast = std::dynamic_pointer_cast<const T>(this);
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
            auto cast = std::dynamic_pointer_cast<T>(this);
            return cast;
        }
        catch (std::bad_cast)
        {
            return nullptr;
        }
    }

}