#pragma once

#include <Cacto/Core/Node.hpp>

namespace cacto
{

    template <typename T>
    inline T *const Node::firstDescendant(const std::string &id) const
    {
        if (this->getId() == id)
        {
            auto node = const_cast<Node *>(this);
            auto cast = dynamic_cast<T *>(node);
            return cast;
        }
        auto childCount = getChildCount();
        for (szt i = 0; i < childCount; i++)
        {
            auto child = getChild(i);
            if (child)
            {
                auto node = child->firstDescendant<T>(id);
                if (node)
                    return node;
            }
        }
        return nullptr;
    }

    template <typename T>
    inline T *const Node::firstAncestor(const std::string &id) const
    {
        if (this->getId() == id)
        {
            auto node = const_cast<Node *>(this);
            auto cast = dynamic_cast<T *>(node);
            return cast;
        }
        auto parent = getParent();
        if (parent)
        {
            auto node = parent->firstAncestor<T>(id);
            return node;
        }
        return nullptr;
    }

}