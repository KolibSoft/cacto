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
        virtual const std::string &getId(const Shared<const T> &value) const = 0;
        virtual Shared<const T> getResource(const std::string &id) const = 0;
        virtual void setResource(const std::string &id, const Shared<const T> &value) = 0;

        Pack();
        virtual ~Pack();

        static const std::string &id(const Shared<const T> &value);
        static Shared<const T> resource(const std::string &id);

        static const std::string NoId;

    private:
        static std::vector<const Pack<T> *> Packs;
    };

}

#include <Cacto/Core/Pack.inl>
