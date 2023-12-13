#ifndef CACTO_NODE_HPP
#define CACTO_NODE_HPP

#include <functional>
#include <Cacto/Lang/XmlConverter.hpp>
#include <Cacto/Core/Export.hpp>

namespace cacto
{

    class Node;

    using NodePredicate = std::function<bool(const Node &node)>;

    class CACTO_CORE_API Node
    {

    public:
        virtual const std::string &getTag() const;

        virtual Node *const getParent() const = 0;

        virtual szt getChildCount() const = 0;
        virtual Node *const getChild(szt index = 0) const = 0;
        i32t getChildIndex(const Node &child) const;

        Node *const firstAncestor(const NodePredicate &predicate) const;
        Node *const firstDescendant(const NodePredicate &predicate) const;

        Node *const firstAncestor(const std::string &tag) const;
        Node *const firstDescendant(const std::string &tag) const;

        Node() = default;
        virtual ~Node() = default;

        static void link(Node &parent, Node &child);
        static void unlink(Node &parent, Node &child);

        static const std::string NoTag;

    protected:
        virtual void onAttach(Node &parent) = 0;
        virtual void onDetach(Node &parent) = 0;

        virtual void onAppend(Node &child) = 0;
        virtual void onRemove(Node &child) = 0;
    };

    template class CACTO_CORE_API XmlConverter<Node>;

    XmlValue CACTO_CORE_API toXml(const Node *const &node);
    void CACTO_CORE_API fromXml(Node *&node, const XmlValue &xml);

    namespace node
    {

        class CACTO_CORE_API XmlConverter
            : public virtual cacto::XmlConverter<Node>
        {
        public:
            XmlConverter() = default;
            virtual ~XmlConverter() = default;
        };

    }

}

#endif