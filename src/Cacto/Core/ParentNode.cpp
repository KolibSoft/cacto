#include <Cacto/Core/ParentNode.hpp>

namespace cacto
{

    ParentNode *const ParentNode::getParent() const
    {
        return nullptr;
    }

    void ParentNode::clearChildren()
    {
        szt childCount = 0;
        while ((childCount = getChildCount()))
        {
            auto child = getChild(childCount - 1);
            if (child)
                remove(*child);
        }
    }

}