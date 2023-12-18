#pragma once

#include <memory>
#include <Cacto/Lang/Export.hpp>

namespace cacto
{

    class CACTO_LANG_API Object
        : public std::enable_shared_from_this<Object>
    {

    public:
        template <typename T = Object>
        Shared<const T> as() const;

        template <typename T = Object>
        Shared<T> as();

        Object() = default;
        virtual ~Object() = default;

    private:
        Object(const Object &other) = delete;
        Object &operator=(const Object &other) = delete;

        Object(Object &&other) = delete;
        Object &operator=(Object &&other) = delete;
    };

}

#include <Cacto/Lang/Object.inl>