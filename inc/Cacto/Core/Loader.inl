#ifndef CACTO_LOADER_INL
#define CACTO_LOADER_INL

#include <Cacto/Core/Loader.hpp>

namespace cacto
{

    template <typename T>
    inline std::shared_ptr<T> Loader<T>::get(i32t id) const
    {
        auto &holder = m_holders[id];
        auto resource = holder.resource.lock();
        if (resource)
            return resource;
        resource = holder.load();
        holder.resource = resource;
        return resource;
    }

    template <typename T>
    inline void Loader<T>::set(i32t id, const std::function<std::shared_ptr<T>()> &load)
    {
        Holder holder{};
        holder.load = load;
        m_holders[id] = holder;
    }

    template <typename T>
    template <typename... As>
    inline void Loader<T>::setLoadFromMemory(i32t id, const As &...args)
    {
        set(id,
            [=]() -> std::shared_ptr<T>
            {
                auto resource = std::make_shared<T>();
                auto result = resource->loadFromMemory(args...);
                return resource;
            });
    }

    template <typename T>
    template <typename... As>
    inline void Loader<T>::setLoadFromStream(i32t id, const As &...args)
    {
        set(id,
            [=]() -> std::shared_ptr<T>
            {
                auto resource = std::make_shared<T>();
                auto result = resource->loadFromStream(args...);
                return resource;
            });
    }

        template <typename T>
    template <typename... As>
    inline void Loader<T>::setLoadFromFile(i32t id, const As &...args)
    {
        set(id,
            [=]() -> std::shared_ptr<T>
            {
                auto resource = std::make_shared<T>();
                auto result = resource->loadFromFile(args...);
                return resource;
            });
    }

    template <typename T>
    template <typename... As>
    inline void Loader<T>::setOpenFromMemory(i32t id, const As &...args)
    {
        set(id,
            [=]() -> std::shared_ptr<T>
            {
                auto resource = std::make_shared<T>();
                auto result = resource->openFromMemory(args...);
                return resource;
            });
    }

    template <typename T>
    template <typename... As>
    inline void Loader<T>::setOpenFromStream(i32t id, const As &...args)
    {
        set(id,
            [=]() -> std::shared_ptr<T>
            {
                auto resource = std::make_shared<T>();
                auto result = resource->openFromStream(args...);
                return resource;
            });
    }

        template <typename T>
    template <typename... As>
    inline void Loader<T>::setOpenFromFile(i32t id, const As &...args)
    {
        set(id,
            [=]() -> std::shared_ptr<T>
            {
                auto resource = std::make_shared<T>();
                auto result = resource->openFromFile(args...);
                return resource;
            });
    }

    template <typename T>
    template <typename... As>
    inline void Loader<T>::setLoadFromImage(i32t id, const As &...args)
    {
        set(id,
            [=]() -> std::shared_ptr<T>
            {
                auto resource = std::make_shared<T>();
                auto result = resource->loadFromImage(args...);
                return resource;
            });
    }

    template <typename T>
    template <typename... As>
    inline void Loader<T>::setLoadFromSamples(i32t id, const As &...args)
    {
        set(id,
            [=]() -> std::shared_ptr<T>
            {
                auto resource = std::make_shared<T>();
                auto result = resource->loadFromSamples(args...);
                return resource;
            });
    }

    template <typename T>
    inline Loader<T>::Loader() = default;

    template <typename T>
    inline Loader<T>::~Loader() = default;

}

#endif