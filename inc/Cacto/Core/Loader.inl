#ifndef CACTO_LOADER_INL
#define CACTO_LOADER_INL

#include <Cacto/Core/Loader.hpp>

namespace cacto
{

    template <typename T>
    inline std::shared_ptr<T> Loader<T>::get() const
    {
        auto resource = m_resource.lock();
        if (!resource)
            resource = std::shared_ptr<T>(m_load());
        m_resource = resource;
        return resource;
    }

    template <typename T>
    inline Loader<T>::Loader(const std::function<T *()> &load)
        : m_resource(),
          m_load(load)
    {
    }

    template <typename T>
    inline Loader<T>::~Loader() = default;

    template <typename T>
    inline Loader<T> Loader<T>::fromMemory(const void *data, szt size)
    {
        Loader<T> loader{
            [=]() -> T *
            {
                auto resource = new T();
                auto _ = resource->loadFromMemory(data, size);
                return resource;
            }};
        return loader;
    }

    template <typename T>
    inline Loader<T> Loader<T>::fromStream(sf::InputStream &stream)
    {
        Loader<T> loader{
            [=]() -> T *
            {
                auto resource = new T();
                auto _ = resource->loadFromStream(stream);
                return resource;
            }};
        return loader;
    }

    template <typename T>
    inline Loader<T> Loader<T>::fromFile(const std::filesystem::path &filename)
    {
        Loader<T> loader{
            [=]() -> T *
            {
                auto resource = new T();
                auto _ = resource->loadFromFile(filename);
                return resource;
            }};
        return loader;
    }

}

#endif