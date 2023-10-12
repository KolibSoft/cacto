#ifndef CACTO_OBJECT_HPP
#define CACTO_OBJECT_HPP

#include <memory>
#include <Cacto/Core/Export.hpp>

namespace cacto
{

    class CACTO_CORE_API Object
        : public std::enable_shared_from_this<Object>
    {

    public:
        template <typename T>
        std::shared_ptr<T> as();

        Object(const Object &) = delete;
        Object &operator=(const Object &) = delete;

        Object();
        virtual ~Object();
    };

}

#include <Cacto/Core/Object.inl>

#endif