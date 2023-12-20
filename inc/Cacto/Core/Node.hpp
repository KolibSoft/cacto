#pragma once

#include <Cacto/Lang/XmlConverter.hpp>
#include <Cacto/Core/Export.hpp>

namespace cacto
{

    class Node;

    class CACTO_CORE_API Node
    {

    public:
        virtual const std::string &getId() const;

        virtual Shared<Node> getParent() const = 0;

        virtual szt getChildCount() const = 0;
        virtual Shared<Node> getChild(szt index = 0) const = 0;
        i32t getChildIndex(const Shared<const Node> &child) const;

        template <typename T = Node>
        Shared<T> firstDescendant(const std::string &id) const;

        template <typename T = Node>
        Shared<T> firstAncestor(const std::string &id) const;

        Node() = default;
        virtual ~Node() = default;

        static void link(const Shared<Node> &parent, const Shared<Node> &child);
        static void unlink(const Shared<Node> &parent, const Shared<Node> &child);

        static const std::string NoId;

    protected:
        virtual void onAttach(const Shared<Node> &parent) = 0;
        virtual void onDetach(const Shared<Node> &parent) = 0;

        virtual void onAppend(const Shared<Node> &child) = 0;
        virtual void onRemove(const Shared<Node> &child) = 0;
    };

    template class CACTO_CORE_API XmlConverter<Node>;

    XmlValue CACTO_CORE_API toXml(const Shared<const Node> &node);
    void CACTO_CORE_API fromXml(Shared<Node> &node, const XmlValue &xml);

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