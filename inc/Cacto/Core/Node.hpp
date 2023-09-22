#ifndef CACTO_NODE_HPP
#define CACTO_NODE_HPP

#include <memory>
#include <Cacto/Core/Export.hpp>

namespace cacto
{

    class Node;
    using SharedNode = std::shared_ptr<Node>;

    class CACTO_CORE_API Node
    {

    public:
        virtual Node *const getParent() const;

        virtual szt getChildCount() const;
        virtual SharedNode getChild(szt index = 0) const;

        Node();
        virtual ~Node();

    protected:
        void onAppend(const SharedNode &child);
        void onRemove(const SharedNode &child);

        virtual void onAttach(Node &parent);
        virtual void onDetach(Node &parent);
    };

}

#endif