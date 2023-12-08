#ifndef CACTO_PACK_HPP
#define CACTO_PACK_HPP

#include <vector>

namespace cacto
{

    template <typename T>
    class Pack
    {

    public:
        Pack();
        virtual ~Pack();

        static std::vector<const Pack<T> *> Packs;
    };

}

#include <Cacto/Core/Pack.inl>

#endif