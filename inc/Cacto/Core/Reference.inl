#pragma once

#include <Cacto/Core/Morph.hpp>
#include <Cacto/Core/Reference.hpp>

namespace cacto
{

    template <typename T>
    inline bool Reference<T>::isOwning() const
    {
        return m_isOwning;
    }

    template <typename T>
    inline Reference<T>::Reference(T &borrowing)
        : Reference(nullptr, false)
    {
        m_instance = &borrowing;
        m_isOwning = false;
    }

    template <typename T>
    inline Reference<T>::Reference(T &&moving)
        : Reference(nullptr, false)
    {
        m_instance = new T(std::move(moving));
        m_isOwning = true;
    }

    template <typename T>
    inline Reference<T>::Reference(T *instance, bool owned)
        : m_instance(instance),
          m_isOwning(owned)
    {
    }

    template <typename T>
    inline Reference<T>::~Reference()
    {
        drop();
    }

    template <typename T>
    inline Reference<T>::Reference(const Reference<T> &other)
        : Reference(nullptr, false)
    {
        *this = other;
    }

    template <typename T>
    inline Reference<T> &Reference<T>::operator=(const Reference<T> &other)
    {
        drop();
        m_instance = other.m_instance;
        m_isOwning = false;
        return *this;
    }

    template <typename T>
    inline Reference<T>::Reference(Reference<T> &&other)
        : Reference(nullptr, false)
    {
        *this = std::move(other);
    }

    template <typename T>
    inline Reference<T> &Reference<T>::operator=(Reference<T> &&other)
    {
        drop();
        m_instance = other.m_instance;
        m_isOwning = other.m_isOwning;
        other.m_instance = nullptr;
        other.m_isOwning = false;
        return *this;
    }

    template <typename T>
    inline Reference<T>::operator bool() const
    {
        return m_instance != nullptr;
    }

    template <typename T>
    inline bool Reference<T>::operator==(const Reference<T> &other) const
    {
        return m_instance == other.m_instance;
    }

    template <typename T>
    inline T &Reference<T>::operator*() const
    {
        return *m_instance;
    }

    template <typename T>
    inline T *Reference<T>::operator->() const
    {
        return m_instance;
    }

    template <typename T>
    inline void Reference<T>::drop()
    {
        if (m_instance && m_isOwning)
        {
            delete m_instance;
            m_instance = nullptr;
            m_isOwning = false;
        }
    }

}