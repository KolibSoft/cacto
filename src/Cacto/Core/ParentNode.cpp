#include <Cacto/Core/ChildNode.hpp>
#include <Cacto/Core/ParentNode.hpp>

namespace cacto
{

    Node *const ParentNode::getParent() const
    {
        return nullptr;
    }

    void ParentNode::clearChildren()
    {
        szt childCount = 0;
        while ((childCount = getChildCount()))
        {
            auto child = dynamic_cast<ChildNode *>(getChild(childCount - 1));
            if (child)
                remove(*child);
        }
    }

}