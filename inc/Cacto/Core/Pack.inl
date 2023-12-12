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
    inline const std::string *const Pack<T>::id(const T &value)
    {
        for (auto &pack : Pack<T>::Packs)
        {
            const std::string * id = pack->getId(value);
            if (id)
                return id;
        }
        return nullptr;
    }

    template <typename T>
    inline const T *const Pack<T>::resource(const std::string &id)
    {
        for (auto &pack : Pack<sf::String>::Packs)
        {
            const T * value = pack->getResource(id);
            if (value)
                return value;
        }
        return nullptr;
    }

    template <typename T>
    inline std::vector<const Pack<T> *> Pack<T>::Packs{};

}