#include <algorithm>
#include <Cacto/Core/Pack.hpp>

namespace cacto
{

    template <typename T>
    inline Pack<T>::Pack()
    {
        Packs.push_back(this);
    }

    template <typename T>
    inline Pack<T>::~Pack()
    {
        Packs.erase(std::remove(Packs.begin(), Packs.end(), this), Packs.end());
    }

    template <typename T>
    inline const std::string &Pack<T>::id(const T &value)
    {
        for (auto &pack : Pack<T>::Packs)
        {
            const std::string &id = pack->getId(value);
            if (id != NoId)
                return id;
        }
        return NoId;
    }

    template <typename T>
    inline const T *const Pack<T>::resource(const std::string &id)
    {
        if (id == NoId)
            return nullptr;
        for (auto &pack : Pack<T>::Packs)
        {
            const T *value = pack->getResource(id);
            if (value != nullptr)
                return value;
        }
        return nullptr;
    }

    template <typename T>
    inline const std::string Pack<T>::NoId{""};

    template <typename T>
    inline std::vector<const Pack<T> *> Pack<T>::Packs{};

}