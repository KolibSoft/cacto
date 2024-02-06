#pragma once

#include <utility>
#include <Cacto/Graphics/Skeleton.hpp>

namespace cacto
{

    inline Skeleton &&Skeleton::setId(const std::string &value) &&
    {
        return std::move(setId(value));
    }

    inline Skeleton &&Skeleton::append(ChildNode &child, const Options &options) &&
    {
        return std::move(append(child, options));
    }

    inline Skeleton &&Skeleton::append(ChildNode &&child, const Options &options) &&
    {
        return std::move(append(std::move(child), options));
    }

}