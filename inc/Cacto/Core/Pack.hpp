#ifndef CACTO_PACK_HPP
#define CACTO_PACK_HPP

#include <string>
#include <vector>

namespace cacto
{

    template <typename T>
    class Pack
    {

    public:
        Pack();
        virtual ~Pack();

        virtual const T *const getResource(const std::string &id) const = 0;
        virtual void setResource(const std::string &id, const T *const value) = 0;

        static std::vector<const Pack<T> *> Packs;
    };

}

#include <Cacto/Core/Pack.inl>

#endif