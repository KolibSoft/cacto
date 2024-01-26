#pragma once

#include <string>
#include <Cacto/Lang/XmlConverter.hpp>
#include <Cacto/Core/Export.hpp>

namespace cacto
{

    class Node;
    class ParentNode;
    class ChildNode;

    class CACTO_CORE_API Node
    {

    public:
        virtual const std::string &getId() const = 0;

        virtual ParentNode *const getParent() const = 0;

        virtual szt getChildCount() const = 0;
        virtual ChildNode *const getChild(szt index = 0) const = 0;
        i32t getChildIndex(const ChildNode &child) const;

        template <typename T = Node>
        T *const firstDescendant(const std::string &id) const;

        template <typename T = Node>
        T *const firstAncestor(const std::string &id) const;

        bool hasDescendant(const Node &node) const;
        bool hasAncestor(const Node &node) const;

        Node() = default;
        virtual ~Node() = default;
    };

    class CACTO_CORE_API ParentNode
        : public virtual Node
    {

    public:
        ParentNode *const getParent() const override;
        void clearChildren();

        virtual void append(ChildNode &child) = 0;
        virtual void remove(ChildNode &child) = 0;

        ParentNode() = default;
        virtual ~ParentNode() = default;
    };

    class CACTO_CORE_API ChildNode
        : public virtual Node
    {

    public:
        szt getChildCount() const override;
        ChildNode *const getChild(szt index = 0) const override;

        virtual void attach(ParentNode &parent) = 0;
        virtual void detach() = 0;

        ChildNode() = default;
        virtual ~ChildNode() = default;
    };

    template class CACTO_CORE_API XmlConverter<Node>;

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