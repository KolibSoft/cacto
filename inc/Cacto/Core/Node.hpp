#ifndef CACTO_NODE_HPP
#define CACTO_NODE_HPP

#include <Cacto/Lang/XmlConverter.hpp>
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
        using Holder = node::Holder;

        virtual const std::string &getTag() const;

        const Node *const find(const std::string &tag) const;
        Node *const find(const std::string &tag);

        virtual Node *const getParent() const = 0;

        virtual szt getChildCount() const = 0;
        virtual Node *const getChild(szt index = 0) const = 0;

        i32t getChildIndex(const Node &child) const;
        i32t getChildIndex(Node &&child) const = delete;

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