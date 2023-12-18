#include <Cacto/Core/Object.hpp>

namespace cacto
{

    template <typename T>
    inline bool Object::is() const
    {
        bool result = dynamic_cast<const T *>(this);
        return result;
    }

    template <typename T>
    inline std::shared_ptr<const T> Object::as() const
    {
        try
        {
            auto self = shared_from_this();
            auto result = std::dynamic_pointer_cast<const T>(self);
            return result;
        }
        catch (std::bad_cast)
        {
            return nullptr;
        }
    }

    template <typename T>
    inline std::shared_ptr<T> Object::as()
    {
        try
        {
            auto self = shared_from_this();
            auto result = std::dynamic_pointer_cast<T>(self);
            return result;
        }
        catch (std::bad_cast)
        {
            return nullptr;
        }
    }

}