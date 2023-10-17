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
        virtual Node *const getParent() const = 0;

        virtual szt getChildCount() const = 0;
        virtual SharedNode getChild(szt index = 0) const = 0;

        Node() = default;
        virtual ~Node() = default;

        static void link(Node &parent, const SharedNode &child);
        static void link(Node &&parent, const SharedNode &child) = delete;

        static void unlink(Node &parent, const SharedNode &child);
        static void unlink(Node &&parent, const SharedNode &child) = delete;

    protected:
        virtual void onAppend(const SharedNode &child) = 0;
        virtual void onRemove(const SharedNode &child) = 0;

        virtual void onAttach(Node &parent) = 0;
        virtual void onAttach(Node &&parent) = delete;

        virtual void onDetach(Node &parent) = 0;
        virtual void onDetach(Node &&parent) = delete;
    };

}

#endif