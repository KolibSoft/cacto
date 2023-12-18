#pragma once

#include <string>
#include <vector>
#include <Cacto/Config.hpp>

namespace cacto
{

    template <typename T>
    class Pack
    {

    public:
        virtual const std::string *const getId(const T &value) const = 0;
        virtual const T *const getResource(const std::string &id) const = 0;
        virtual void setResource(const std::string &id, const T *const value) = 0;

        Pack();
        virtual ~Pack();

        static const std::string *const id(const T &value);
        static const T *const resource(const std::string &id);

    private:
        static std::vector<const Pack<T> *> Packs;
    };

}

#include <Cacto/Core/Pack.inl>
