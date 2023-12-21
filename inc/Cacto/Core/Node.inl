#include <Cacto/Core/Node.hpp>

namespace cacto
{

    template <typename T>
    inline T *const Node::firstDescendant(const std::string &id) const
    {
        if (this->getId() == id)
        {
            auto node = const_cast<Node *>(this);
            return node;
        }
        for (szt i = 0; i < getChildCount(); i++)
        {
            auto child = getChild(i);
            if (child)
            {
                auto node = child->firstDescendant<T>(id);
                if (node)
                    return std::move(node);
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
            return node;
        }
        auto parent = getParent();
        if (parent)
        {
            auto node = parent->firstAncestor<T>(id);
            return std::move(node);
        }
        return nullptr;
    }

}