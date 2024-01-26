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
        virtual const std::string &getId(const T &value) const = 0;
        virtual const T *const getResource(const std::string &id) const = 0;

        Pack();
        virtual ~Pack();

        static const std::string &id(const T &value);
        static const T *const resource(const std::string &id);

        static const std::string NoId;

    private:
        static std::vector<const Pack<T> *> Packs;
    };

    template <typename T>
    const std::string &getId(const T &value);

    template <typename T>
    const T *const getResource(const std::string &id);

}

#include <Cacto/Core/Pack.inl>
