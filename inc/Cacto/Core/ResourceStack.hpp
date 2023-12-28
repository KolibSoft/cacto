#pragma once

#include <memory>
#include <vector>
#include <Cacto/Config.hpp>

namespace cacto
{

    template <typename T>
    class ResourceStack
    {

    public:
        szt getSize() const;
        void push(const std::shared_ptr<T> &resource);
        void push(const std::vector<std::shared_ptr<T>> &resources);
        std::shared_ptr<T> pop();
        std::vector<std::shared_ptr<T>> pop(szt count);

        ResourceStack();
        virtual ~ResourceStack();

    private:
        std::vector<std::shared_ptr<T>> m_resources;
    };

}

#include <Cacto/Core/ResourceStack.inl>