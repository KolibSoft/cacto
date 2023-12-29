#pragma once

#include <Cacto/Core/ResourceStack.hpp>

namespace cacto
{

    template <typename T>
    inline szt ResourceStack<T>::getSize() const
    {
        return m_resources.size();
    }

    template <typename T>
    inline void ResourceStack<T>::push(const std::shared_ptr<T> &resource)
    {
        m_resources.push_back(resource);
    }

    template <typename T>
    inline void ResourceStack<T>::push(const std::vector<std::shared_ptr<T>> &resources)
    {
        m_resources.insert(m_resources.end(), resources.begin(), resources.end());
    }

    template <typename T>
    inline std::shared_ptr<T> ResourceStack<T>::pop()
    {
        auto top = m_resources.back();
        m_resources.pop_back();
        return std::move(top);
    }

    template <typename T>
    inline std::vector<std::shared_ptr<T>> ResourceStack<T>::pop(szt count)
    {
        std::vector<std::shared_ptr<T>> top{m_resources.end() - count, m_resources.end()};
        m_resources.erase(m_resources.end() - count, m_resources.end());
        return std::move(top);
    }

    template <typename T>
    inline ResourceStack<T>::ResourceStack()
        : m_resources()
    {
    }

    template <typename T>
    inline ResourceStack<T>::~ResourceStack() = default;

}