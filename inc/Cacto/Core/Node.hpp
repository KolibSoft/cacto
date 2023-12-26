#pragma once

#include <Cacto/Lang/XmlConverter.hpp>
#include <Cacto/Core/ResourceStack.hpp>
#include <Cacto/Core/Export.hpp>

namespace cacto
{

    class Node;

    class CACTO_CORE_API Node
    {

    public:
        virtual const std::string &getId() const = 0;

        virtual Node *const getParent() const = 0;

        virtual szt getChildCount() const = 0;
        virtual Node *const getChild(szt index = 0) const = 0;
        i32t getChildIndex(const Node &child) const;

        template <typename T = Node>
        T *const firstDescendant(const std::string &id) const;

        template <typename T = Node>
        T *const firstAncestor(const std::string &id) const;

        Node() = default;
        virtual ~Node() = default;

        bool hasDescendant(const Node &node) const;
        bool hasAncestor(const Node &node) const;

        static ResourceStack<Node> XmlStack;
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

#include <Cacto/Core/Node.inl>