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

        virtual void append(const SharedNode &child);
        virtual void remove(const SharedNode &child);

        Node();
        virtual ~Node();

    protected:
        virtual void onAttach(Node& parent);
        virtual void onDetach(Node& parent);
    };

}

#endif