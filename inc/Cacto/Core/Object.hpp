#pragma once

#include <memory>
#include <Cacto/Core/Export.hpp>

namespace cacto
{

    class CACTO_CORE_API Object
        : public std::enable_shared_from_this<Object>
    {

    public:
        template <typename T = Object>
        bool is() const;

        template <typename T = Object>
        std::shared_ptr<const T> as() const;

        template <typename T = Object>
        std::shared_ptr<T> as();

        Object() = default;
        virtual ~Object() = default;

    private:
        Object(const Object &other) = delete;
        Object &operator=(const Object &other) = delete;

        Object(Object &&other) = delete;
        Object &operator=(Object &&other) = delete;
    };

}

#include <Cacto/Core/Object.inl>