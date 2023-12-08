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
    inline std::vector<const Pack<T> *> Pack<T>::Packs{};

}