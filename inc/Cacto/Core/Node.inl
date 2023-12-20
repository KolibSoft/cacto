#include <Cacto/Lang/Object.hpp>
#include <Cacto/Core/Node.hpp>

namespace cacto
{

    template <typename T>
    inline Shared<T> Node::firstDescendant(const std::string &id) const
    {
        if (this->getId() == id)
        {
            auto object = dynamic_cast<Object *>(const_cast<Node *>(this));
            if (object)
                return object->as<T>();
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
    inline Shared<T> Node::firstAncestor(const std::string &id) const
    {
        if (this->getId() == id)
        {
            auto object = dynamic_cast<Object *>(const_cast<Node *>(this));
            if (object)
                return object->as<T>();
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