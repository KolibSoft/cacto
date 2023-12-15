#include <Cacto/Core/Node.hpp>

namespace cacto
{

    template <typename T>
    inline T *const Node::firstAncestor(const std::string &tag) const
    {
        auto node = firstAncestor([&](const Node &node)
                                  { return node.getTag() == tag; });
        return dynamic_cast<T *>(node);
    }

    template <typename T>
    inline T *const Node::firstDescendant(const std::string &tag) const
    {
        auto node = firstDescendant([&](const Node &node)
                                    { return node.getTag() == tag; });
        return dynamic_cast<T *>(node);
    }

}