#ifndef CACTO_LOADER_HPP
#define CACTO_LOADER_HPP

#include <memory>
#include <functional>
#include <filesystem>
#include <Cacto/Config.hpp>

namespace sf
{
    class InputStream;
}

namespace cacto
{

    template <typename T>
    class Loader
    {

    public:
        std::shared_ptr<T> get() const;

        Loader(const std::function<T *()> &load);
        virtual ~Loader();

        Loader(const Loader<T> &other) = delete;
        Loader &operator=(const Loader<T> &other) = delete;

        Loader(Loader<T>&& temp) = default;
        Loader &operator=(Loader<T>&& temp) = default;

        static Loader<T> fromMemory(const void *data, szt size);
        static Loader<T> fromStream(sf::InputStream& stream);
        static Loader<T> fromFile(const std::filesystem::path& filename);

    private:
        mutable std::weak_ptr<T> m_resource;
        std::function<T *()> m_load;
    };

}

#include <Cacto/Core/Loader.inl>

#endif