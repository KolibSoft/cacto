#ifndef CACTO_NODE_HPP
#define CACTO_NODE_HPP

#include <Cacto/Core/Export.hpp>

namespace cacto
{

    namespace node
    {
        class Holder;
    }

    class CACTO_CORE_API Node
    {

    public:
        virtual Node *const getParent() const = 0;

        virtual szt getChildCount() const = 0;
        virtual Node *const getChild(szt index = 0) const = 0;

        i32t getChildIndex(const Node &child) const;
        i32t getChildIndex(Node &&child) const = delete;

        Node() = default;
        virtual ~Node() = default;

        static void link(Node &parent, Node &child);
        static void unlink(Node &parent, Node &child);

    protected:
        using Holder = node::Holder;

        virtual void onAttach(Node &parent) = 0;
        virtual void onDetach(Node &parent) = 0;

        virtual void onAppend(Node &child) = 0;
        virtual void onRemove(Node &child) = 0;
    };

    namespace node
    {

        class CACTO_CORE_API Holder
        {

        public:
            Node &getNode() const;

            Holder(Node &node);
            virtual ~Holder();

        private:
            Node *m_node;
        };

    }

}

#endif