#ifndef CACTO_LOADER_HPP
#define CACTO_LOADER_HPP

#include <memory>
#include <functional>
#include <unordered_map>
#include <Cacto/Config.hpp>

namespace cacto
{

    template <typename T>
    class Loader
    {

    public:
        std::shared_ptr<T> get(i32t id) const;
        void set(i32t id, const std::function<std::shared_ptr<T>()> &load);

        template <typename... As>
        void setLoadFromMemory(i32t id, const As &...args);

        template <typename... As>
        void setLoadFromStream(i32t id, const As &...args);

        template <typename... As>
        void setLoadFromFile(i32t id, const As &...args);

        template <typename... As>
        void setOpenFromMemory(i32t id, const As &...args);

        template <typename... As>
        void setOpenFromStream(i32t id, const As &...args);

        template <typename... As>
        void setOpenFromFile(i32t id, const As &...args);

        template <typename... As>
        void setLoadFromImage(i32t id, const As &...args);

        template <typename... As>
        void setLoadFromSamples(i32t id, const As &...args);

        Loader();
        virtual ~Loader();

    private:
        struct Holder
        {
            Holder() = default;
            virtual ~Holder() = default;

            std::weak_ptr<T> resource;
            std::function<std::shared_ptr<T>()> load;
        };

        mutable std::unordered_map<u32t, Holder> m_holders;
    };

}

#include <Cacto/Core/Loader.inl>

#endif